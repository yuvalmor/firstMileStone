
#include "ConnectCommand.h"
#include "TableManager.h"
#include "Var.h"
#include "ShuntingYard.h"

#include <iostream>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

using namespace std;
#define CONNECTIONS_LIMIT 5
#define BUFFER_SIZE 1024
#define NUM_PARAMETERS 3
#define FIRST_EXP_LOC 1
#define SECOND_EXP_LOC 2

ConnectCommand::ConnectCommand(vector<string> line) {

    // Checks if the input is valid
    if (line.size() != NUM_PARAMETERS) {
        throw exception();
    }

    this->ip = line.at(FIRST_EXP_LOC);
    string portExp = line.at(SECOND_EXP_LOC);
    ShuntingYard* sy = ShuntingYard::getInstance();
    this->port = (int)sy->calculateSYard(portExp)->calculate();
}

void ConnectCommand::doCommand() {

    int retCode = connectToServer(this->ip, this->port);

    if (retCode < 0 ) {
        throw "problem while connecting ";
    }

}

int ConnectCommand::connectToServer(string ip, int port) {

    // 1) create a socket
    int listener = socket(AF_INET, SOCK_STREAM, 0);

    if (listener < 0) {

        cout << "can't create socket" << endl;
        return -1;

    }

    // 2) connect socket to an ip address and a port

    // a) create a socket address variable for the server we are connecting
    sockaddr_in address;
    //bzero((char*)&address, sizeof(address));

    struct hostent *server;

    // b) connect the socket to port number, need to convert the port to big endian
    //    since our computer uses little endian and the network works with big endian
    //    this is achieved by using htons function.
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &address.sin_addr);

    if ( connect(listener, (sockaddr*)&address, sizeof(address)) < 0 ) {

        cout << "can't connect socket to port" << endl;
        return -2;

    }

    // 3) save socket to  struct

    Threader *t = Threader::getInstance();
    t->setClientSocket(listener);

    // don't close keep open

    return 0;

}
