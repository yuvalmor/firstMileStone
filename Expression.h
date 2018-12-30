#ifndef SIMULATOR9492YN_EXPRESSION_H
#define SIMULATOR9492YN_EXPRESSION_H

using namespace std;

// Expression is abstract
// everything will be an expression.
// for new - we have : Num as independent derived class
//                     BinaryExpression - everything else.

class Expression {
public:
    /*
     * output - a double
     * operation - returns the value of the expression
     */
    virtual double calculate()=0;

};

#endif //SIMULATOR9492YN_EXPRESSION_H