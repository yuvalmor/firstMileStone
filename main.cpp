#include "Runner.h"

int main (int argc, char* argv[]) {
    try{
        Runner runner;
        runner.run(argc, argv);
    }catch(...) {
        throw "could not run program";
    }
    return 0;
}
