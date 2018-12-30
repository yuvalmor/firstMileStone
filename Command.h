#ifndef SIMULATOR9492YN_MASTER_COMMAND_H
#define SIMULATOR9492YN_MASTER_COMMAND_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Command is an abstract class,
 * That has pure virtual method - doCommand.
 * All the commands in the program inherit this class.
 */
class Command {
public:
    virtual void doCommand()=0;
};

#endif
