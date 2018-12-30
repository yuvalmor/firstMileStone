#ifndef NEWSIMULATOR_LEXER_H
#define NEWSIMULATOR_LEXER_H

#include <string>
#include <vector>

using namespace std;

/**
 * The lexer responsible to split the line into words (vector of strings).
 */
class Lexer{
    // The input line
    string line;
public:
    // Set the data member line
    void setLine(string line){this->line = line;}
    // Do the analysis and split the line into words
    vector<string> lexicalAnalysis ();
    // Support function
    string separateOperations();
};

#endif