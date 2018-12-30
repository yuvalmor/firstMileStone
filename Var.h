
#ifndef SIMULATOR9492YN_MASTER_VAR_H
#define SIMULATOR9492YN_MASTER_VAR_H

#include "Expression.h"
#include "TableManager.h"
#include <string>

#include <map>
#include <unordered_map>


// var holds characters as variables of an expression
class Var: public Expression {
private:
    // var stores the variable, vars is the current map of variables
    string var;

public:
    // constructor
    Var(string variable) {
        this->var = variable;
    }

    string getVar() const {
        return this->var;
    }


    double calculate() override {

        TableManager* tableManager = TableManager::getInstance();

        Threader* threader = Threader::getInstance();
        threader->getThreader().mut->lock();

        if (tableManager->getStringToValueMap().count(this->var) > 0) {
            double value = tableManager->getStringToValueMap()[this->var];
            threader->getThreader().mut->unlock();
            return value;

        } else {
            threader->getThreader().mut->unlock();
            throw "variable does not exist";
        }

    }

};

#endif //SIMULATOR9492YN_MASTER_VAR_H
