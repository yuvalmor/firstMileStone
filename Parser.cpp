#define OPEN_SERVER "openDataServer"
#define CONNECT_TO_SERVER "connect"
#define VAR_DEFINITION "var"
#define WHILE_LOOP "while"
#define IF_CONDITION "if"
#define BIND_DEFINITION "bind"
#define PRINT_DEFINITION "print"
#define SLEEP_DEFINITION "sleep"
#define BIND_LOCATION 3
#define LEFT_EXPRESSION_LOCATION 1
#define RIGHT_EXPRESSION_LOCATION 3
#define CONDITION_LOCATION 2
// complex condition location
#define COMPLEX_CONDITION_LOC 3
#define FIRST_OPERATOR 2
#define SECOND_OPERATOR 3
#define UPDATE_VAR_PARAMETERS 3
#define ASSIGN_LOCATION 1

#include "Parser.h"
#include <regex>

/**
 * The function createBoolExp interpret the line and create boolean expression.
 * The boolean expression will be used by the conditions commands (while and.
 */
BooleanExpression* Parser::createBoolExp() {
    ShuntingYard* shuntingYard = ShuntingYard::getInstance();
    // Calculate using the Shunting Yard algorithm the left expression
    Expression* leftExp = shuntingYard->calculateSYard(line.at(LEFT_EXPRESSION_LOCATION));
    // Calculate using the shunting Yard algorithm the right expression
    Expression* rightExp;
    string condition;
    // If the condition contain two operator such as: ==,!=,<=,>= it will merge them to one.
    if(strcmp(line.at(COMPLEX_CONDITION_LOC).c_str(),"=") == 0){
        condition = line.at(FIRST_OPERATOR)+line.at(SECOND_OPERATOR);
        rightExp = shuntingYard->calculateSYard(line.at(RIGHT_EXPRESSION_LOCATION+1));
    } else{
        rightExp = shuntingYard->calculateSYard(line.at(RIGHT_EXPRESSION_LOCATION));
        condition = line.at(CONDITION_LOCATION);
    }
    // Create the boolean expression
    BooleanExpression* conditionExp = new BooleanExpression(leftExp,condition,rightExp);
    return conditionExp;
}

/**
 * The function ParserAnalysis, parser the line that he holds as a data member.
 * Each line represent different command to preform,
 * So it create the appropriate command, and activate it.
 */
void Parser::parserAnalysis() {
    Command* command = nullptr;
    if(getFirstWord() == OPEN_SERVER){
        command = new OpenServerCommand(line);
    }
    if(getFirstWord()== CONNECT_TO_SERVER){
        command = new ConnectCommand(line);
    }
    if(getFirstWord() == VAR_DEFINITION){
        if(line.at(BIND_LOCATION) == BIND_DEFINITION){
            // Define new variable that have bind to the simulator
            command = new BindCommand(line);
        } else {
            // Define new variable ("local variable")
            command = new DefineCommand(line);
        }
    }
    if (line.size() == UPDATE_VAR_PARAMETERS && line.at(ASSIGN_LOCATION) == "=") {
        // Create command from type update variable
        command = new UpdateVarCommand(line);
    }
    if (getFirstWord() == SLEEP_DEFINITION) {
        // Create sleep command
        command = new SleepCommand(line);
    }
    if(getFirstWord() == PRINT_DEFINITION){
        command = new PrintCommand(line);
    }
    // If the line describe while loop, it will create while command
    if(getFirstWord() == WHILE_LOOP){
        BooleanExpression* conditionExp = createBoolExp();
        ConditionCommand* conditionCommand = new WhileCommand(conditionExp);
        addConditionCommand(conditionCommand);
    }
    // If the line describe if condition, it will create if command
    if(getFirstWord() == IF_CONDITION){
        // Create the condition expression that need to be checked
        BooleanExpression* conditionExp = createBoolExp();
        ConditionCommand* conditionCommand = new IfCommand(conditionExp);
        addConditionCommand(conditionCommand);
    }
    // If the line contain the character } it means that the condition command is done
    if(line.at(line.size()-1) == "}" && !conditionCommands.empty()){
        command = getConditionCommand();
        command->doCommand();
        return;
    }
    // If there is no condition command open, and the command isn't null pointer, do the command
    if(conditionCommands.empty() && command!= nullptr){
        command->doCommand();
    }
    // If there is condition command open, add the command to the last condition command
    if(!conditionCommands.empty() && command!= nullptr){
        conditionCommands.at(conditionCommands.size()-1)->addCommand(command);
    }
}

