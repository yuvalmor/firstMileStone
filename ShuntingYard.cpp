
#include "ShuntingYard.h"
#include "TableManager.h"
#include "Threader.h"
#include "Num.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiply.h"
#include "Divide.h"
#include "Neg.h"
#include "Var.h"

#include <list>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <stdlib.h>
#include <sstream>

#define LETTER_BOTTOM 96
#define LETTER_TOP 123
#define NUM_BOTTOM 47
#define NUM_TOP 58
#define CAPITAL_DIFFER 32
#define SPACE 32
#define TAB 9

using namespace std;

bool ShuntingYard::isNumber(string str) {
    int dotCount=0;
    /*
     * checking the first char of the string as long as the string
     * is not empty, insuring there is only 1 decimal point and
     * there are only numbers.
     */
    while (!str.empty()) {
        switch (str.at(0))
        {
            case '.' :
                if (++dotCount<=1) {
                    // cuts the first char of the string
                    str = str.substr(1, str.size()-1);
                    break;
                }
                return false;
            default:
                // 0-9 in ascii
                if ((str.at(0) > NUM_BOTTOM) && (str.at(0) < NUM_TOP)) {
                    str = str.substr(1, str.size()-1);
                    break;
                }
                return false;
        }
    }
    return true;
}

bool ShuntingYard::isOperator(char c) {

     // checking if c is -*:+
    switch (c) {
        case '*':
            return true;
        case '+':
            return true;
        case '-':
            return true;
        case '/':
            return true;
        default:
            return false;
    }

}

bool ShuntingYard::opsPriority(char c, string lastChar) {

    /*
     * operators priority is :
     * 1) ~
     * 2) * :
     * 3) + -
     * 4) ()
     *
     * to consider - small or equal relations, for example
     * + is prior not only to () but also to another + or -
     */

    // implanting ~ instead of - where the expression is unary
    if (theStack.empty()) {
        if (c == '-' && lastChar == "") {
            theStack.push('~');
            return false;
        } else {
            theStack.push(c);
            return false;
        }
    }

    // insuring no two consecutive **, //, ++ ( -- is allowed)
    if ((c == '*' && lastChar.at(0) == c) || (c == '/' && lastChar.at(0) == c) ||
            (c == '+' && lastChar.at(0) == c)) {
        throw "two illegal consecutive operators";
    }

    // implanting ~ instead of - where the expression is unary
    if   ((isOperator(lastChar.at(0)) || lastChar.at(0) == '(') && c == '-') {
        theStack.push('~');
        return false;
    }

    char top = this->theStack.top();

    // returning priority result based on the map
    switch (top) {
        case '~':
            return true;
        case '*':
            if (c == '(' || c == ')' || c == '-' || c == '+' || c == '*' || c == '/') {
                return true;
            }
        case '/':
            if (c == '(' || c == ')' || c == '-' || c == '+' || c == '*' || c == '/') {
                return true;
            }
        case '+':
            if (c == '(' || c == ')' || c == '-' || c == '+') {
                return true;
            }
        case '-':
            if (c == '(' || c == ')' || c == '-' || c == '+') {
                return true;
            }
        case '(':
            if (c == '(' || c == ')') {
                return true;
            }
        case ')':
            if (c == '(' || c == ')') {
                return true;
            }
        default:
            // if the current operator is prior to the one in the stack we push
            // the current operator to the stack.
            theStack.push(c);
            return false;

    }

}

int ShuntingYard::doubleLength(double number) {

    string strNum = to_string(number);
    int integerInd=0;
    int dotCounter = 0;

    // reducing 0 at the and of the string
    char lastChar = strNum.at(strNum.size() - 1);
    while (lastChar == '0') {
        strNum = strNum.substr(0, strNum.size() - 1);
        lastChar = strNum.at(strNum.size() - 1);
    }

    // if there were only 0 end than a . than it's an integer
    if (lastChar == '.') {
        integerInd++;
    }

    int lengthOfString = strNum.size();

    // counting decimal points
    while (!strNum.empty()) {
        lastChar = strNum.at(strNum.size() - 1);
        if (lastChar == '.') {
            dotCounter++;
        }

        strNum = strNum.substr(0, strNum.size() - 1);
    }

    // for more than 1 decimal point
    if (dotCounter > 1) {
        throw "invalid input - 2 points";
    }

    // for integer, reducing the decimal point count
    if (integerInd) {
        return --lengthOfString;
    }
    return lengthOfString;

}


int ShuntingYard::handleVars(const string &str) {
    string temp = str;
    string var;
    int varLength=0;

    // checking the next char is a letter or a digit
    while ( ((temp.at(0) < LETTER_TOP-CAPITAL_DIFFER) && (temp.at(0) > LETTER_BOTTOM-CAPITAL_DIFFER)) ||
                        ((temp.at(0) < LETTER_TOP) && (temp.at(0) > LETTER_BOTTOM))  ||
                         isNumber(to_string(temp.at(0)))) {

        // concating the char to the variable
        var += temp.at(0);
        varLength++;

        TableManager* tableManager = TableManager::getInstance();
        Threader* threader = Threader::getInstance();
        threader->getThreader().mut->lock();
        int checkExist = tableManager->getStringToValueMap().count(var);
        threader->getThreader().mut->unlock();

        // end of varible when we see an operator, also insuring the var is in the map
        if (checkExist > 0) {
            if ((temp.size() == 1) || (isOperator(temp.at(1)) || temp.at(1) == '(' || temp.at(1) == ')')) {
                return varLength;
            }
        }
        temp = temp.substr(1,temp.size()-1);

    }
    // return 0 for input with illegal chars or unrecognized vars
    return 0;
}

Expression* ShuntingYard::calculateSYard(const string& str) {

    /*
     * this function is the control function for the string we receive.
     * we pass over the chars and navigate them as numbers/vars/operations.
     * when the string is over theQueue holds the postfix order for the expression
     * so we make an expression out of it.
     */

    string temp = str;
    // holds the prior char
    string lastChar;

    while (!temp.empty()) {
        // skip spaces in the string
        if (temp.at(0) == SPACE || temp.at(0) == TAB) {
            temp = temp.substr(1, temp.size()-1);
            continue;
        }

        /*
         * for operator, if their is no greater precedence operator in the
         * stack we push the operator to the stack, if their is one or more
         * we push them tu the queue and pop them from the stack, than
         * pushing the current operator to the stack.
         */
        if (isOperator(temp.at(0))) {
            char c = temp.at(0);
            if (!(this->opsPriority(c, lastChar))) {
                lastChar = temp.substr(0,1);
                temp = temp.substr(1, temp.size() - 1);
                continue;
            } else {
                do {

                    if (theStack.top() == '(' || theStack.top() == ')') {
                        theStack.pop();
                        break;
                    }
                    string s(1, theStack.top());
                    theQueue.push(s);
                    theStack.pop();

                } while (this->opsPriority(c, lastChar));
            }
            lastChar = temp.substr(0,1);
            temp = temp.substr(1, temp.size() - 1);
            continue;
        }

        double number;

        // numbers are pushed to the queue
        if (istringstream(temp) >> number) {
            this->theQueue.push(to_string(number));
            int len = doubleLength(number);
            lastChar = temp.substr(0,1);
            temp = temp.substr(len, temp.size()-len);
            continue;
        }

        // parenthesis ( is pushed to the stack
        if (temp.at(0) == '(') {
            theStack.push('(');
            lastChar = temp.substr(0,1);
            temp = temp.substr(1, temp.size()-1);
            continue;
        }

        /*
         * pop all the operators from the stack onto the queue until
         * we encounter a ) parenthesis, then pushing it to the stack.
         */
        if (temp.at(0) == ')') {
            lastChar = temp.substr(0,1);
            temp = temp.substr(1, temp.size()-1);
            while (!theStack.empty()) {
                if (theStack.top() != '(') {
                    string s(1, theStack.top());
                    theQueue.push(s);
                    theStack.pop();
                } else {
                    theStack.pop();
                    break;
                }
            }
            continue;

        }

        /*
         * for variables we check they exist in the map, then push them
         * to the queue.
         */
        int varLength=handleVars(temp);
        if (varLength >0) {
            string var = temp.substr(0,varLength);
            this->theQueue.push(var);
            lastChar = var;
            temp = temp.substr(varLength, temp.size()-varLength);
            continue;
        }

        throw "illegal note";

    }

    /*
     * pushing all remain operator to the queue
     */
    while (!theStack.empty()) {
        string s(1, theStack.top());
        theStack.pop();
        theQueue.push(s);
    }

    // making one expression from the postfix order
    return makeExpression();


}

Expression* ShuntingYard::makeExpression() {

    // aid stack for calculation
    stack<Expression*> stackExp;

    /*
     * we pull item from the queue. for numbers and vars we push them to
     * the stack (notice we make them expressions first).
     * when we encounter an operator (there are no () in the queue, only
     * *:+- and ~ ) we create a new suitable expression by using the next
     * 2 (or 1 for ~) item in the stack. than we push the expression back
     * to the stack.
     * finally we have one expression at the top of the stack than is a
     * very complex and by using calculate() we can calculate it.
     */

    while (!theQueue.empty()) {
        string exp = theQueue.front();
        theQueue.pop();
        if (isNumber(exp)) {
            double number;
            istringstream(exp) >> number;
            stackExp.push(new Num(number));
            continue;
        }
        if (exp.at(0) == '~') {
            Expression* unary = new Neg(stackExp.top());
            stackExp.pop();
            stackExp.push(unary);
            continue;
        }
        if (isOperator(exp.at(0))) {
            char c = exp.at(0);
            Expression* right = stackExp.top();
            stackExp.pop();
            Expression *left;
            if (stackExp.empty()) {
                throw "binary op needs two parameters";
            } else {
                left = stackExp.top();
                stackExp.pop();
            }
            switch (c) {
                case '+' :
                    stackExp.push(new Plus(left, right));
                    break;
                case '-' :
                    stackExp.push(new Minus(left, right));
                    break;
                case '*' :
                    stackExp.push(new Multiply(left, right));
                    break;
                case '/' :
                    stackExp.push(new Divide(left, right));
                    break;
                default:
                    break;
            }
            continue;
        }

        // using the map of variable to initialize a var

        stackExp.push(new Var(exp));

    }
    return stackExp.top();
}

void ShuntingYard::cleanStackAndQueue() {
    // empty the queue and stack
    while (!theQueue.empty()) {
        theQueue.pop();
    }
    while (!theStack.empty()) {
        theStack.pop();
    }
}