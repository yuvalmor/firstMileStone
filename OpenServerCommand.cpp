#include "OpenServerCommand.h"
#include "ShuntingYard.h"
#include "TableManager.h"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <thread>
#include <chrono>
#include <vector>

#define FIRST_EXP_LOC 1
#define SECOND_EXP_LOC 2
#define CONNECTIONS_LIMIT 5
#define BUFFER_SIZE 1024

using namespace std::chrono_literals;
using namespace std;

OpenServerCommand::OpenServerCommand(vector<string> line) {
    ShuntingYard* shuntingYard = ShuntingYard::getInstance();
    string firstExpression = line.at(FIRST_EXP_LOC);
    string secondExpression = line.at(SECOND_EXP_LOC);
    this->port = (int)shuntingYard->calculateSYard(firstExpression)->calculate();
    this->hz = (int)shuntingYard->calculateSYard(secondExpression)->calculate();
    if( this->port < 0 || this->hz < 0) {
        throw exception();
    }
}

void OpenServerCommand::doCommand() {
    int retCode = openServer(this->port, this->hz);
    if (retCode <0 ) {
        throw "problem in server opening ";
    }
}


int OpenServerCommand::openServer(int port, int Hz) {

    // 1) create a socket
    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        cout << "can't create socket" << endl;
        return -1;
    }

    // 2) bind socket to an ip address and a port

    // a) create a socket address variable
    struct sockaddr_in address, newAddress;
    bzero((char *) &address, sizeof(address));

    // b) bind the socket to port number, need to convert the port to big endian
    //    since our computer uses little endian and the network works with big endian
    //    this is achieved by using htons function.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(listener, (struct sockaddr *) &address, sizeof(address)) < 0) {
        cout << "can't bind socket to port";
        return -2;
    }

    // 3) listen (mark socket for listen- wait for client connection)

    if (listen(listener, CONNECTIONS_LIMIT) < 0) {
        cout << "can't mark socket for listening" << endl;
        return -3;
    }

    // 4) accept a call from a client and save socket to struct
    int client = sizeof(newAddress);
    int newSocket = accept(listener, (struct sockaddr *) &newAddress, (socklen_t *) &client);
    if (newSocket < 0) {
        cout << "can't receive client" << endl;
        return -4;
    }
    createThread(newSocket);
    return 0;
}

void OpenServerCommand::createThread(int socket) {
    Threader *t = Threader::getInstance();
    t->setServerSocket(socket);
    t->setServerHz(this->hz);
    std::thread tServer(TableManager::firstReadFromSimulator, (void *) t);
    tServer.join();
    std::thread tServer2(TableManager::generalReadFromSimulator, (void *) t);
    t->setThreadServer(&tServer2);
    tServer2.detach();
}