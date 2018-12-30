

#ifndef SIMULATOR9492YN_MASTER_NEG_H
#define SIMULATOR9492YN_MASTER_NEG_H

#include "UnaryExpression.h"

class Neg : public UnaryExpression {
public:
    // constructor - uses super class constructor
    Neg(Expression* ex):UnaryExpression(ex){}

    // calculation as negation by -1 multiplication
    double calculate() override{
        return -1 * this->getExp()->calculate();
    }
};

#endif //SIMULATOR9492YN_MASTER_NEG_H
