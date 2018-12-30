#ifndef SIMULATOR9492YN_PLUS_H
#define SIMULATOR9492YN_PLUS_H

#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
    // constructor - uses super class constructor
    Plus(Expression* leftExp, Expression* rightExp):BinaryExpression(leftExp,rightExp){}
    double calculate() override{
        return this->getLeftExp()->calculate() + this->getRightExp()->calculate();
    }
};

#endif //SIMULATOR9492YN_PLUS_H
