#ifndef  SIMULATOR9492YN_MASTER_BOOLEANEXPRESSION_H
#define  SIMULATOR9492YN_MASTER_BOOLEANEXPRESSION_H

#include "Expression.h"
#include <string>

/**
 * BooleanExpression contains two operands (represent as expression),
 * separated by one operator.
 * It produce true(!0) or false(0) when evaluate.
 */
class BooleanExpression : public Expression{
    // Left operand
    Expression* leftExpression;
    // Right operand
    Expression* rightExpression;
    // The operator between the operands
    string condition;
public:
    // Constructor
    BooleanExpression(Expression* left, string condition, Expression* right){
        this-> leftExpression = left;
        this->rightExpression = right;
        this->condition = condition;
    }
    // Calculate the boolean expression
    double calculate() override;
};

#endif
