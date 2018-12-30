#ifndef SIMULATOR9492YN_MASTER_BINDCOMMAND_H
#define SIMULATOR9492YN_MASTER_BINDCOMMAND_H

#define VAR_LOCATION 1
#define BIND_TO_LOCATION 4

#include "Command.h"

class BindCommand : public Command{
    // The variable that we define
    string varName;
    // The path to the simulator - direct path or variable name that holds the path
    string bindTo;
public:
    // Constructor to bind command
    explicit BindCommand(vector<string>line){
        this->varName = line.at(VAR_LOCATION);
        this->bindTo = line.at(BIND_TO_LOCATION);
    }
    // Do the binding between variable and simulator path
    void doCommand() override;
};

#endif
