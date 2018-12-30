
#ifndef SIMULATOR9492YN_SHUNTINGYARD_H
#define SIMULATOR9492YN_SHUNTINGYARD_H

#include "Expression.h"

#include <list>
#include <string>
#include <stack>
#include <queue>
#include <map>

using namespace std;

// ShuntingYard is a static class, responsible for the
// algorithm and works on the input string.
class ShuntingYard {

private:

    // members
    stack<char> theStack;
    queue<string> theQueue;

public:

    // static instance of this class for external approach
    static ShuntingYard* getInstance() {
        static ShuntingYard* instance;
        if (instance == NULL) {
            instance = new ShuntingYard();
        }
        return instance;
    }

    /*
     * input - parted string in current location
     * output - an integer, 0 for non existing variable, positive number
     * for existing variable length.
     * operation - extracting the next variable in the string, returns
     * it's length or 0 for illegal vars.
     */
    int handleVars(const string& str);

    /*
     * input - parted string in current location
     * output - Expression*, based on the given string.
     * operation - the control function , explained on the body. making
     * a postfix order from an infix order.
     */
    Expression* calculateSYard(const string& input);

    /*
     * input - a double
     * output - an integer
     * operation - calculates the length of a double (including decimal part).
     */
    int doubleLength(double number);

    /*
    * input - a char
    * output - true or false
    * operation - checking if a char is an operator :+-*
    */
    bool isOperator(char c);

    /*
    * input - a string
    * output - true or false
    * operation - checking if a string is a number
    */
    bool isNumber(string str);

    /*
    * input - current operator(c) and last char(string)
    * output - true or false
    * operation - returns true if there is an operator with greater
    * precedence from  'c' at the top of the stack, return false
    * and pushes 'c' to the stack otherwise.
    */
    bool opsPriority(char c, string lastChar);

    /*
    * input -
    * output - Expression*
    * operation - this function makes a single complex expression from
    * a queue of orders.
    */
    Expression* makeExpression();

    // operation: empties the members
    void cleanStackAndQueue();

};

#endif //SIMULATOR9492YN_SHUNTINGYARD_H
