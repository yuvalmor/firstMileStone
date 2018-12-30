#ifndef SIMULATOR9492YN_MASTER_COMMAND_H
#define SIMULATOR9492YN_MASTER_COMMAND_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual void doCommand()=0;
};

#endif
