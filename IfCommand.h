#ifndef NEWSIMULATOR_IFCOMMAND_H
#define NEWSIMULATOR_IFCOMMAND_H

#include "ConditionCommand.h"

class IfCommand : public ConditionCommand{
public:
    IfCommand(BooleanExpression* booleanExpression):ConditionCommand(booleanExpression){}
    void doCommand() override;
};

#endif //NEWSIMULATOR_IFCOMMAND_H
