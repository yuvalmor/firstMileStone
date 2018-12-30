

#ifndef SIMULATOR9492YN_MASTER_UNARYEXPRESSION_H
#define SIMULATOR9492YN_MASTER_UNARYEXPRESSION_H

#include "Expression.h"

// UnaryExpression is abstract class
class UnaryExpression:public Expression {
private:
    Expression* exp;

public:

    // constructor
    UnaryExpression(Expression* ex) {
        this->exp = ex;
    }

    // getter
    Expression* getExp() const  {
        return this->exp;
    }

    /*
     * out put - a double
     * operation - returns the value of expression
     * after negation action (multiplying by -1)
     */
    virtual double calculate()=0;

};

#endif //SIMULATOR9492YN_MASTER_UNARYEXPRESSION_H
