#include "WhileCommand.h"
#include <iostream>

void WhileCommand::doCommand() {

    BooleanExpression* boolExp = this->getBoolExpression();
    vector<Command*> toExecute = this->getCommands();
    while(boolExp->calculate()){
        for(auto x: toExecute){
            x->doCommand();
        }
    }
}