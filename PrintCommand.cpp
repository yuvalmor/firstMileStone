#include "PrintCommand.h"
#include "ShuntingYard.h"
#include <regex>
#define PRINTABLE_LOC 1
#define CUT_IN_SUB_STR 3
#define SUB_STR_INITIAL 1

PrintCommand::PrintCommand(vector<string> line) {
    regex reg ("\"");
    smatch match;
    string toPrint;
    regex_search(line.at(PRINTABLE_LOC),match,reg);
    // In case its a string, cut the spaces and merge it to one word
    if(!match.empty()){
        for(int i=1; i<line.size(); i++){
            toPrint += line.at(i) + " ";
        }
        // Remove the quotation mark and the last space from the string
        toPrint = toPrint.substr(SUB_STR_INITIAL,toPrint.size()-CUT_IN_SUB_STR);
        this->toPrint=toPrint;
        this->isVar=false;
    } else{
        this->toPrint = line.at(PRINTABLE_LOC);
        this->isVar=true;
    }
}

void PrintCommand::doCommand() {
    ShuntingYard* shuntingYard = ShuntingYard::getInstance();
    if(isVar){
        double calculate = shuntingYard->calculateSYard(this->toPrint)->calculate();
        cout << to_string(calculate) << endl;
    } else {
        cout << toPrint << endl;
    }
}