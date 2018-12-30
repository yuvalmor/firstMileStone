

#ifndef SIMULATOR9492YN_MASTER_CONNECTCOMMAND_H
#define SIMULATOR9492YN_MASTER_CONNECTCOMMAND_H

#include "Command.h"
#include "Threader.h"
#include <string>
#include <vector>

using namespace std;

class ConnectCommand : public Command {

private:

    string ip;
    int port;

public:

    explicit ConnectCommand(vector<string>line);

    void doCommand() override;

    int connectToServer(string ip, int port);

};

#endif //SIMULATOR9492YN_MASTER_CONNECTCOMMAND_H


