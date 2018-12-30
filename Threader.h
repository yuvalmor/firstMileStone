
#ifndef SIMULATOR9492YN_MASTER_THREADER_H
#define SIMULATOR9492YN_MASTER_THREADER_H

#include <string>
#include <thread>
#include <mutex>

using namespace std;

struct threadData {

    int serverSocket;

    int clientSocket;

    int hz;

    string var;

    double value;

    mutex* mut;

    thread* tServer;

};

class Threader {

private:

    threadData tData;
public:

    threadData getThreader() const {
        return this->tData;
    }

    void setServerSocket(int serverSocket) {
        this->tData.serverSocket = serverSocket;
    }

    void setClientSocket(int clientSocket) {
        this->tData.clientSocket = clientSocket;
    }

    void setServerHz(int hz) {
        this->tData.hz = hz;
    }

    void setMutex(mutex* m) {
        this->tData.mut = m;
    }

    void setVarString(const string& var) {
        this->tData.var = var;
    }

    void setValue(double value) {
        this->tData.value = value;
    }

    void setThreadServer(thread* t) {
        this->tData.tServer = t;
    }

    static Threader* getInstance(){
        static Threader* instance;
        if (instance == NULL) {
            instance = new Threader();
        }
        return instance;
    }


};

#endif //SIMULATOR9492YN_MASTER_THREADER_H
