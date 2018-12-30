#ifndef NEWSIMULATOR_BOOLEANEXPRESSION_H
#define NEWSIMULATOR_BOOLEANEXPRESSION_H

#include "Expression.h"
#include <vector>
#include <string>

class BooleanExpression : public Expression{
    Expression* leftExpression;
    Expression* rightExpression;
    string condition;
public:
    BooleanExpression(Expression* left, string condition, Expression* right){
        this-> leftExpression = left;
        this->rightExpression = right;
        this->condition = condition;
    }
    double calculate() override;
};

#endif //NEWSIMULATOR_BOOLEANEXPRESSION_H
