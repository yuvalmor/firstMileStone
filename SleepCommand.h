
#ifndef SIMULATOR9492YN_MASTER_SLEEP_H
#define SIMULATOR9492YN_MASTER_SLEEP_H
#define TIME_LOCATION 1

#include "Command.h"
#include "ShuntingYard.h"
#include "TableManager.h"
#include <unistd.h>
#include <string>
#include <iostream>

class SleepCommand : public Command {
    unsigned int sleepDuration;
public:
    explicit SleepCommand(vector<string> line){

        ShuntingYard* shuntingYard = ShuntingYard::getInstance();
        this->sleepDuration = (unsigned int)shuntingYard->
                calculateSYard(line.at(TIME_LOCATION))->calculate();

    }
    void doCommand() override{

        this_thread::sleep_for(chrono::milliseconds(this->sleepDuration));
    }

};

#endif //SIMULATOR9492YN_MASTER_SLEEP_H
