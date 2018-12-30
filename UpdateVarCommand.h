

#ifndef SIMULATOR9492YN_MASTER_UPDATEVARCOMMAND_H
#define SIMULATOR9492YN_MASTER_UPDATEVARCOMMAND_H

#include "Command.h"
#include <string>
#include <vector>

using namespace std;

class UpdateVarCommand : public Command{

private:
    string var;
    string value;

public:

    UpdateVarCommand(vector<string> line) {
        this->var = line.at(0);
        this->value = line.at(2);
    }

    void doCommand() override;

};


#endif //SIMULATOR9492YN_MASTER_UPDATEVARCOMMAND_H
