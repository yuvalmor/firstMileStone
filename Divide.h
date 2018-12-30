#ifndef SIMULATOR9492YN_DIVIDE_H
#define SIMULATOR9492YN_DIVIDE_H

#include "BinaryExpression.h"

class Divide : public BinaryExpression {
public:
    // constructor - uses super class constructor
    Divide(Expression* leftExp, Expression* rightExp):BinaryExpression(leftExp,rightExp){}

    double calculate() override{
        if(this->getRightExp()->calculate() == 0){
            throw "cannot divide by 0";
        }
        return this->getLeftExp()->calculate() / this->getRightExp()->calculate();
    }
};

#endif //SIMULATOR9492YN_DIVIDE_H