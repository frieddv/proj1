//
// Created by ariel on 12/24/18.
//

#include "Parser.h"

vector<ICommand*> Parser::Parse(queue<string> tokens) {
    vector<ICommand*> commands;
    while (!tokens.empty()) {
        Commands id = GetCommandId(tokens);
        if (IsContainer(id))
            commands.push_back(CreateContainerCmd(tokens, id));
        else
            commands.push_back(CreateCommand(tokens, id));
    }
    return commands;
}

Commands Parser::GetCommandId(queue<string> &tokens) {
    Commands id = IdentifyCommand(tokens.front());
    if (id != SET_VAR)
        tokens.pop();
    return id;
}

ICommand* Parser::CreateCommand(queue<string> &tokens, Commands id) {
    string varName;
    queue<string> expression;
    switch(id) {
        case SET_VAR:
            varName = ExtractToken(tokens);
            if (ExtractToken(tokens) != "=")
                perror(SYNTAX_ERROR);
            while (IsWithinExpression(tokens))
                expression.push(ExtractToken(tokens));
            //IExpression *ex = ShuntingYard(expression);
            //return new UpdateVarCmd(...);
            break;
        case OPEN_DATA_SERVER:
            break;
        case CONNECT:
            break;
        case PRINT:
            if (IsString(tokens.front())) {
                string toPrint = ExtractToken(tokens);
                ConfirmLineEnd(tokens);
                return new PrintStrCmd(toPrint);
            }
            else {
                
            }
            break;
        case SLEEP:
            while (IsWithinExpression(tokens))
                expression.push(ExtractToken(tokens));
            //IExpression *ex = ShuntingYard(expression);
            //return new SleepCmd(ex);
            break;
        case DEFINE_VAR:
            varName = ExtractToken(tokens);
            break;
        default:
            perror("something went wrong with Parser::Parse!");
    }
}

bool Parser::IsString(string token) const { return token[0] == '\"'; }

void Parser::ConfirmLineEnd(queue<string> &tokens) {
    if (tokens.front() != "\n")
        perror(SYNTAX_ERROR);
    else
        tokens.pop();
}

bool Parser::IsWithinExpression(queue<string> &tokens) {
    string currentToken = tokens.front();
    return ((currentToken != "\n") && (currentToken != "{") && (currentToken != "}"));
}

string Parser::ExtractToken(queue<string> &tokens) {
    string temp = tokens.front();
    tokens.pop();
    return temp;
}

Commands Parser::IdentifyCommand(string firstToken) {
    if (firstToken =="connect")
        return CONNECT;
    if (firstToken =="openDataServer")
        return OPEN_DATA_SERVER;
    if (firstToken == "print")
        return PRINT;
    if (firstToken == "sleep")
        return SLEEP;
    if (firstToken == "while")
        return WHILE;
    if (firstToken == "if")
        return IF;
    if (firstToken == "var")
        return DEFINE_VAR;
    return SET_VAR;
}

bool Parser::IsContainer(Commands id) {
    return id == IF || id == WHILE;
}
