
#include <iostream>
#include "DefineCommand.h"

#define VAR_NAME_LOCATION 1
#define EXPRESSION_LOCATION 3
#define NUM_PARAMETERS 4

DefineCommand::DefineCommand(vector<string> line){
    // Checks if the input valid, and throw exception if its not
    if(line.size() != NUM_PARAMETERS){
        throw exception();
    }
    ShuntingYard* shuntingYard = ShuntingYard::getInstance();
    // Take the name of the var from the line
    this->varName = line.at(VAR_NAME_LOCATION);
    // Calculate using the shunting yard algorithm the variable value
    this->value = shuntingYard->calculateSYard(line.at(EXPRESSION_LOCATION))->calculate();
    cout << "var name = " <<varName <<endl;
    cout << "value = " << value << endl;
}

void DefineCommand::doCommand() {
    TableManager* tableManager = TableManager::getInstance();
    if (!(tableManager->isVarInTable(this->varName))) {
        tableManager->updateLocalVar(this->varName, this->value);
    } else {
        throw  exception();
    }
}