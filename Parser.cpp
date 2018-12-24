//
// Created by ariel on 12/24/18.
//

#include "Parser.h"

vector<ICommand*> Parser::parse(queue<string> tokens) {
    vector<ICommand*> commands;
    while (!tokens.empty()) {
        string cmdID = popFromQueue(tokens);
    }

    return commands;
}

string Parser::popFromQueue(queue<string> &tokens) {
    string temp = tokens.front();
    tokens.pop();
    return temp;
}
