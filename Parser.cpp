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
        TrimLeadingEndline(tokens);
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
    IExpression *expression;
    switch(id) {
        case SET_VAR:
            varName = ExtractToken(tokens);
            if (ExtractToken(tokens) != "=")
                perror(SYNTAX_ERROR);
            expression = ExtractExpression(tokens);
            //return new UpdateVarCmd(...);
            break;
        case OPEN_DATA_SERVER:
            break;
        case CONNECT:
            break;
        case PRINT:
            if (IsString(tokens.front())) {
                string toPrint = ExtractToken(tokens);
                return new PrintStrCmd(toPrint);
            }
            else {
                
            }
            break;
        case SLEEP:
            return new SleepCmd(ExtractExpression(tokens));
        case DEFINE_VAR:
            varName = ExtractToken(tokens);
            if (ExtractToken(tokens) != "=")
                perror(SYNTAX_ERROR);
            if (tokens.front() != "bind")
                return new DefineVarCmd(manager, varName, ExtractExpression(tokens));
            else {
                tokens.pop();
                return new DefineVarCmd(manager, varName, ExtractToken(tokens));
            }
        default:
            perror("something went wrong with Parser::Parse!");
    }
}

IExpression* Parser::ExtractExpression(queue<string> &tokens) {
    queue<string> rawExpression;
    while(IsWithinExpression(tokens))
        rawExpression.push(ExtractToken(tokens));
    return ShuntingYard(rawExpression);
}

bool Parser::IsString(string token) const { return token[0] == '\"'; }

void Parser::TrimLeadingEndline(queue<string> &tokens) {
    if (!(tokens.front() != "\n"))
        tokens.pop();
}

bool Parser::IsWithinExpression(queue<string> tokens) {
    string nextToken = tokens.front();
    return ((nextToken != "\n") && (nextToken != "{") && (nextToken != "}"));
}

bool Parser::IsWithinFirstExp(string previousToken, queue<string> tokens) {
    if (!IsWithinExpression(tokens))
        return false;
    string nextToken = tokens.front();
    if ((previousToken == "(") || (nextToken == ")"))
        return true;
    if ((WhatSign(previousToken) != INVALID) || (WhatSign(nextToken) != INVALID))
        return true;
    return false;
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
