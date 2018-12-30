
#ifndef SIMULATOR9492YN_MASTER_TABLEMANAGER_H
#define SIMULATOR9492YN_MASTER_TABLEMANAGER_H

#include <unordered_map>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <chrono>
#include <unistd.h>
#include <sys/socket.h>
#include <thread>
#include <mutex>
#include <vector>
#include "Threader.h"
#include "Expression.h"

#define ENTER 10
#define MILLI_IN_SECONDS 1000
#define BUFFER_SIZE 1024
#define SET_VALUES 23

using namespace std::chrono_literals;
using namespace std;

class TableManager {

    unordered_map<string, double> pathToValue;
    unordered_map<int, string> orderToPath;

    // main tables
    unordered_map<string, double> stringToValue;
    unordered_map<string, string> stringToPath;
    unordered_map<string, vector<string>> pathTostring;

public:

    static TableManager* getInstance(){
        static TableManager* instance;
        if (instance == NULL) {
            instance = new TableManager();
        }
        return instance;
    }

    int getAddressesFromFile() ;
    void bindStringToPath(const string& var, const string& path);
    bool isVarInTable(const string& varName) ;
    bool isVarBindToAddress(const string& varName);
    string getVarAddress(const string& varName);
    string cut23Values(string str) ;
    void updateTheTables(string values) ;
    double getVarValue(const string& var);
    void updateLocalVar(const string& var, double value) ;
    void updateClientData(const string& var, double num) ;
    void informSimulator(const string& path) ;


    unordered_map<string,double> getStringToValueMap() const {
        return this->stringToValue;
    }

    static void* firstReadFromSimulator(void* t) {

        TableManager* tableManager = TableManager::getInstance();
        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);

        ssize_t readValue = read(((Threader *) t)->getThreader().serverSocket, buffer, BUFFER_SIZE);

        string str = string(buffer);

        str = tableManager->cut23Values(str);
    }

    static void* generalReadFromSimulator(void* t) {

        TableManager* tableManager = TableManager::getInstance();
        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);

        ssize_t readValue = 0;

        double timeRound = (double)MILLI_IN_SECONDS/((Threader *) t)->getThreader().hz;
        string str1;

        while (readValue!=-1) {

            auto currentTime = chrono::steady_clock::now();

            readValue = read(((Threader *)t)->getThreader().serverSocket, buffer, BUFFER_SIZE);

            if (!str1.empty()) {
                str1 += string(buffer);
                str1 = tableManager->cut23Values(str1);
            } else {
                str1 = string(buffer);
                str1 = tableManager->cut23Values(str1);
            }
            bzero(buffer, BUFFER_SIZE);
            auto endTime = chrono::steady_clock::now();
            double timeUsed = chrono::duration_cast<chrono::milliseconds>(endTime-currentTime).count();
            double remained = timeRound-timeUsed;
            if (remained > 0) {

                this_thread::sleep_for(std::chrono::milliseconds((int)remained));
            }
        }

        cout << "simulator done sending / problem while reading from simulator" << endl;

    }




};

#endif //SIMULATOR9492YN_MASTER_TABLEMANAGER_H
