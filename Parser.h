#ifndef NEWSIMULATOR_PARSER_H
#define NEWSIMULATOR_PARSER_H

#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "Expression.h"
#include "ConditionCommand.h"
#include "BooleanExpression.h"
#include "TableManager.h"
#include "ShuntingYard.h"
#include "BinaryExpression.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "BindCommand.h"
#include "DefineCommand.h"
#include "UpdateVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

class Parser{
    // Vector that save all the open condition commands in the program
    vector<ConditionCommand*> conditionCommands;
    // The line that the parser works on
    vector<string> line;
public:
    // Set the line that the parser analyse
    void setLine(vector<string> input){
        this->line = input;
    }
    // Return the first word in the line
    string getFirstWord(){
        return this->line.at(0);
    }
    // Add condition command to the
    void addConditionCommand(ConditionCommand* conditionCommand){
        this->conditionCommands.push_back(conditionCommand);
    }
    // Return the last condition command and remove it from the vector
    ConditionCommand* getConditionCommand(){
        ConditionCommand* conditionCommand;
        conditionCommand = this->conditionCommands.at(conditionCommands.size()-1);
        this->conditionCommands.pop_back();
        return conditionCommand;
    }
    // Function that create boolean expression
    BooleanExpression* createBoolExp();
    // Do the parser analysis, and turn the line to the appropriate command
    void parserAnalysis();
};

#endif
