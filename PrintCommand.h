#ifndef SIMULATOR9492YN_MASTER_PRINTCOMMAND_H
#define SIMULATOR9492YN_MASTER_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command{
    string toPrint;
    bool isVar;
public:
    // Constructor
    explicit PrintCommand(vector<string>line);
    // Printing the input
    void doCommand() override;
};

#endif
