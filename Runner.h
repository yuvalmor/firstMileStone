#ifndef SIMULATOR9492YN_MASTER_RUNNER_H
#define SIMULATOR9492YN_MASTER_RUNNER_H

#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "TableManager.h"
#include "ShuntingYard.h"

using namespace std;

class Runner {
mutex mu;
public:

    void runTheProgram(const string& line, Lexer* lexer, Parser* parser) {
        lexer->setLine(line);
        parser->setLine(lexer->lexicalAnalysis());
        parser->parserAnalysis();
    }
    //main function
    void run(int argc, char* argv[]) {
        // download addresses from file
        TableManager *tableManager = TableManager::getInstance();
        int paths = tableManager->getAddressesFromFile();
        if (paths < 0) {
            cout << "problem with paths" << endl;
            return;
        }
        // set mutex variable
        Threader *threader = Threader::getInstance();
        threader->setMutex(&mu);
        Lexer lexer;
        Parser parser;
        string line;
        if (argc > 1) {
            string fileName = argv[1];
            ifstream file(fileName);
            if (file.is_open()) {
                while (getline(file, line)) {
                    runTheProgram(line, &lexer, &parser);
                }
                file.close();
            }
       /* } else {
            cout << "insert output" <<endl;
            bool flag = true;
            while (flag) {
                getline(cin, line);
                if (!line.empty()) {
                    runTheProgram(line, &lexer, &parser);
                } else {
                    flag = false;
                }
            }
            return;
        }*/
        } else {
            return;
        }
        close(threader->getThreader().serverSocket);
        close(threader->getThreader().clientSocket);
    }
};

#endif