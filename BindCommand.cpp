#include "BindCommand.h"
#include "TableManager.h"
#include <regex>

/**
 * Bind command - responsible to bind variables to the relevant path in the simulator.
 * When we want to bind the variable,
 * we need to get as input a direct path to the relevant place in the simulator,
 * or Alternative to get other variable that holds the path.
 */
void BindCommand::doCommand() {
    TableManager* tableManager = TableManager::getInstance();
    // Put address pattern in the regex
    regex reg ("[\"/][a-z/-]+[\"]");
    smatch match;
    regex_search(bindTo,match,reg);
    // If we found match, it means that we got address and we can bind it to the variable
    if(!match.empty()){
        // Cut the quotation marks from the path
        string path = bindTo.substr(1, bindTo.size()-2);
        // Add the variable name and its path to the relevant table
        tableManager->bindStringToPath(varName,path);
    } else {
        // Checks if the variable has an address
        if(tableManager->isVarBindToAddress(bindTo)){
            // Get the variable address from the table manager
            string address = tableManager->getVarAddress(bindTo);
            // Bind the address for the new variable
            tableManager->bindStringToPath(varName,address);
            // Update the initial value of the variable in the relevant table
            double value = tableManager->getVarValue(bindTo);
            tableManager->updateLocalVar(varName,value);
        } else{
            // Cant bind variable to other variable that dose not have address!
            throw exception();
        }
    }
}