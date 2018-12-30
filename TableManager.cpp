

#include "TableManager.h"

int TableManager::getAddressesFromFile() {

    ifstream file;
    file.open("addresses.txt");
    if (file.bad()) {
        cout << "file problem" << endl;
        return -1;
    }

    string address;
    int index=0;
    while (file >> address) {
        this->orderToPath[index] = address;
        index++;
    }

    file.close();
    return 0;
}

void TableManager::bindStringToPath(const string& var, const string& path) {

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    //  enter var and path to stringToPath table
    this->stringToPath[var] = path;

    this->stringToValue[var] = this->pathToValue[path];

    // add another var to vector of the known path
    vector<string> temp = this->pathTostring[path];
    temp.push_back(var);
    this->pathTostring[path] = temp;

    threader->getThreader().mut->unlock();

}

bool TableManager::isVarInTable(const string& varName) {

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    bool ans = false;

    if (this->stringToValue.count(varName) > 0) {
        ans = true;
    }

    threader->getThreader().mut->unlock();

    return ans;
}

bool TableManager::isVarBindToAddress(const string& varName){

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    bool ans =  (bool)stringToPath.count(varName);

    threader->getThreader().mut->unlock();

    return ans;
}

string TableManager::getVarAddress(const string& varName){

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    string address = stringToPath[varName];

    threader->getThreader().mut->unlock();

    return address;
}

string TableManager::cut23Values(string str) {

    TableManager* tableManager = TableManager::getInstance();
    string temp;

    while (str.at(0) != ENTER) {

        temp += str.at(0);
        str = str.substr(1, str.size() - 1);
    }

    str = str.substr(1, str.size() - 1);

    tableManager->updateTheTables(temp);

    return str;
}

void TableManager::updateTheTables(string values) {

    Threader* threader = Threader::getInstance();
    string value;
    int index =0 ;

    while (index < SET_VALUES) {
        bool checkValues = values.empty();
        if (!checkValues && values.at(0) != ',') {
            value += values.at(0);
        } else {

            threader->getThreader().mut->lock();

            double number = stod(value);
            string path = this->orderToPath[index];
            this->pathToValue[path] = number;

            vector<string> v = (this->pathTostring[path]);
            vector<string>:: iterator itr;
            for( itr = v.begin(); itr != v.end(); itr++) {
                this->stringToValue[*itr] = number;
            }

            threader->getThreader().mut->unlock();

            index++;
            value="";
        }

        if (!checkValues) {
            values = values.substr(1, values.size() - 1);
        }

    }
}

double TableManager::getVarValue(const string& var) {
    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    double value = this->stringToValue[var];

    threader->getThreader().mut->unlock();
}

void TableManager::updateLocalVar(const string& var, double value) {

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();
    this->stringToValue[var] = value;
    threader->getThreader().mut->unlock();

}

void TableManager::updateClientData(const string& var, double num) {

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    string path = this->stringToPath[var];

    // sending the new var info
    threader->setVarString(var);
    threader->setValue(num);
    informSimulator(path);

    // sending info on other binded vars only if the vector contains more than 1 var
    vector<string> v = (this->pathTostring[path]);

    if (v.size() > 1) {
        vector<string>:: iterator itr;
        for( itr = v.begin(); itr != v.end(); itr++) {
            this->stringToValue[*itr] = num;
        }
    }

    threader->getThreader().mut->unlock();

}

void TableManager::informSimulator(const string& path) {

    Threader* threader = Threader::getInstance();
    string line = "set " + path + " " + to_string(threader->getThreader().value) + string("\r\n");
    ssize_t writeValue = write(threader->getThreader().clientSocket,line.c_str(), line.length());

    if (writeValue < 0) {
        throw "problem while writing to simulator";
    }

}