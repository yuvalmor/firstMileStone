#ifndef NEWSIMULATOR_DEFINECOMMAND_H
#define NEWSIMULATOR_DEFINECOMMAND_H

#include "Command.h"
#include "Expression.h"
#include "ShuntingYard.h"
#include "TableManager.h"

class DefineCommand : public Command{
    // The variable name
    string varName;
    // The variable value
    double value;
public:
    // Constructor
    explicit DefineCommand(vector<string> line);
    // Define new var, and save it in the relevant table
    void doCommand() override;
};

#endif //NEWSIMULATOR_DEFINECOMMAND_H
