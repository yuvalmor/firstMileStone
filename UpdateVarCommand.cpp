
#include "UpdateVarCommand.h"
#include "ShuntingYard.h"
#include "ConnectCommand.h"
#include "TableManager.h"

#include <netinet/in.h>

using namespace std;


void UpdateVarCommand::doCommand() {

    ShuntingYard* sy = ShuntingYard::getInstance();

    double varValue = sy->calculateSYard(this->value)->calculate();

    TableManager* tableManager = TableManager::getInstance();

    // check if variable is local
    if(tableManager->isVarBindToAddress(this->var)){
        // not local

        // update the var - value table
        tableManager->updateLocalVar(this->var, varValue);

        // update other variables and inform simulator
        tableManager->updateClientData(this->var, varValue);

    } else{

        // only a local variable update
        tableManager->updateLocalVar(this->var, varValue);

    }

}