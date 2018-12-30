#ifndef SIMULATOR9492YN_NUM_H
#define SIMULATOR9492YN_NUM_H

#include "Expression.h"

class Num : public Expression {
private:
    double number;
public:
    Num(double number){
        this->number = number;
    }
    double calculate() override{
        return this->number;
    }
};

#endif //SIMULATOR9492YN_NUM_H