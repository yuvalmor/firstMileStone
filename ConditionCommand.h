#ifndef SIMULATOR9492YN_MASTER_CONDITIONCOMMAND_H
#define SIMULATOR9492YN_MASTER_CONDITIONCOMMAND_H

#include "Command.h"
#include "BooleanExpression.h"

/**
 * All the commands that depends in condition
 */
class ConditionCommand : public Command{
    // The condition
    BooleanExpression* booleanExpression;
    // All the commands to perform if the condition is true
    vector<Command*> commands;
public:
    // Constructor to condition command
    explicit ConditionCommand(BooleanExpression* booleanExpression){
        this->booleanExpression = booleanExpression;
    }
    // Add command to perform
    void addCommand (Command* command){
        this->commands.push_back(command);
    }
    // Return all the commands to perform
    vector<Command*> getCommands(){
        return this->commands;
    }
    // Return the boolean expression
    BooleanExpression* getBoolExpression(){
        return this->booleanExpression;
    }
    // Do the command
    virtual void doCommand()=0;
};

#endif //NEWSIMULATOR_CONDITIONCOMMAND_H
