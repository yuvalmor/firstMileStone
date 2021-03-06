#include "Lexer.h"
#include <regex>

/**
 * The function separateOperations get string line,
 * And add spaces before and after the operators: !,<,>,=.
 * It returns the new fixed line.
 */
string Lexer::separateOperations() {
    int i =0;
    string fixedLine;
    // Pass on every character in the line
    while (i < line.length()){
        // If the character is an operator
        if(line[i] =='=' || line[i] =='!' || line[i] =='<' || line[i] =='>'){
            fixedLine = fixedLine + " " + line[i] + " ";
        } else {
            fixedLine = fixedLine + line[i];
        }
        // Move on to the next character
        i++;
    }
    // Return the fixed line
    return fixedLine;
}

/**
 * The function checkMatch checks if the regex pattern match the string.
 * Return true if the pattern exist in the string and false otherwise.
 */
bool checkMatch (regex regexPattern, string str){
    smatch match;
    regex_search(str,match,regexPattern);
    // If there is a match, return true, and false otherwise
    if(!match.empty()){
        return true;
    }
    return false;
}

/**
 * The function checkUniqueCharacters - checks the first and the last character in the word.
 * If one of them is a unique character, it update the boolean pointers head and back.
 * When update the boolean pointers to false -
 * It means that they need to join to the next or the previuos token.
 */
void checkUniqueCharacters(string word,bool* head,bool* back){
    string str;
    regex regOperator ("[-*/+]");
    regex leftBracket ("[(]");
    regex rightBracket ("[)]");
    bool matchingAnswer;
    char start = word[0];
    char end = word[word.length()-1];
    // Push the first character in the word
    str.push_back(start);
    matchingAnswer = checkMatch(leftBracket, str);
    if(matchingAnswer) {
        *head = true;
        *back = false;
        return;
    }
    matchingAnswer = checkMatch(rightBracket, str);
    if(matchingAnswer) {
        *head = false;
    } else{
        matchingAnswer = checkMatch(regOperator,str);
        if(matchingAnswer){
            *head = false;
        } else {
            *head = true;
        }
    }
    // Pop the first character in the word
    str.pop_back();
    // Push the last character in the word
    str.push_back(end);
    matchingAnswer = checkMatch(leftBracket,str);
    if(matchingAnswer){
        *back = false;
        return;
    }
    matchingAnswer = checkMatch(rightBracket,str);
    if(matchingAnswer){
        *head = false;
        *back = true;
        return;
    }
    matchingAnswer = checkMatch(regOperator,str);
    if(matchingAnswer) {
        *back = false;
        return;
    } else {
        *back = true;
    }
}

/**
 * The function lexicalAnalysis
 */
vector<string> Lexer::lexicalAnalysis() {
    vector<string> commands;

    string str = separateOperations();
    string buffer;
    regex whiteSpace ("[^\n\t ]+");
    smatch match;
    bool flag = false;
    bool front;
    bool back;
    while (regex_search(str,match,whiteSpace)){
        buffer = match.str((0));
        str = match.suffix().str();
        checkUniqueCharacters(buffer,&front,&back);
        if(flag && commands.size()>0){
            string temp = commands.back();
            temp = temp+buffer;
            commands.pop_back();
            commands.push_back(temp);
        } else{
            if(front){
                commands.push_back(buffer);
            } else {
                if(commands.size()>1 && !checkMatch(regex("[<=>]"),commands[commands.size()-1])){
                    string temp = commands.back();
                    temp = temp+buffer;
                    commands.pop_back();
                    commands.push_back(temp);
                } else{
                    commands.push_back(buffer);
                }
            }
        }
        if(!back){
            flag = true;
        } else{
            flag = false;
        }
    }
    return commands;
}
