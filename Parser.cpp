//
// Created by ariel on 12/24/18.
//

#include "Parser.h"

vector<ICommand*> Parser::Parse(queue<string> tokens) {
    vector<ICommand*> commands;
    while (!tokens.empty()) {
        string cmdID = ExtractToken(tokens);

    }
    return commands;
}

string Parser::ExtractToken(queue<string> &tokens) {
    string temp = tokens.front();
    tokens.pop();
    return temp;
}

Commands Parser::IdentifyCommand(string firstToken) {
    if (firstToken =="connect")
        return ConnectCmd;
    if (firstToken =="openDataServer")
        return OpenDataServerCmd;
    if (firstToken == "print")
        return PrintCmd;
    if (firstToken == "sleep")
        return SleepCmd;
    if (firstToken == "while")
        return WhileCmd;
    if (firstToken == "if")
        return IfCmd;
    if (firstToken == "var")
        return DefineCmd;
    return VarCmd;
}
