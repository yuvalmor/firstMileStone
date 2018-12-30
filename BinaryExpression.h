#ifndef SIMULATOR9492YN_BINARYEXPRESSION_H
#define SIMULATOR9492YN_BINARYEXPRESSION_H

#include "Expression.h"

/**
 * Binary Expression contains two operands (represent as expression),
 * separated by one operator.
 */
class BinaryExpression : public Expression{
    // Left operand
    Expression* leftExp;
    // Right operand
    Expression* rightExp;
public:
    // Constructor
    BinaryExpression(Expression* left, Expression* right){
        this->leftExp = left;
        this->rightExp = right;
    }
    // Get left operand
    Expression* getLeftExp() const{
        return this->leftExp;
    }
    // Get right operand
    Expression* getRightExp() const{
        return this->rightExp;
    }
    // Calculate the expression
    virtual double calculate()=0;
};

#endif