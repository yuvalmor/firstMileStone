#include "BooleanExpression.h"

/**
 * Return the result of the condition
 */
double BooleanExpression::calculate() {
    if(this->condition == "=="){
        return leftExpression->calculate() == rightExpression->calculate();
    }
    if(this->condition == ">="){
        return leftExpression->calculate() >= rightExpression->calculate();
    }
    if(this->condition == "<="){
        return leftExpression->calculate() <= rightExpression->calculate();
    }
    if(this->condition == "!="){
        return leftExpression->calculate() != rightExpression->calculate();
    }
    if(this->condition == "<"){
        return leftExpression->calculate() < rightExpression->calculate();
    }
    if(this->condition == ">"){
        return leftExpression->calculate() > rightExpression->calculate();
    }
    return 0;
}