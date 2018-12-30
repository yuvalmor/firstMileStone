

#ifndef SIMULATOR9492YN_MASTER_OPENSERVERCOMMAND_H
#define SIMULATOR9492YN_MASTER_OPENSERVERCOMMAND_H

#include "Command.h"
#include "Threader.h"
#include <string>
#include <vector>

using namespace std;

class OpenServerCommand : public Command {

    int port;
    int hz;

public :

    explicit OpenServerCommand(vector<string>line);

    void doCommand() override;

    int openServer(int port, int Hz);

    void createThread(int socket) ;

};

#endif //SIMULATOR9492YN_MASTER_OPENSERVERCOMMAND_H
