//
// Created by ariel on 12/24/18.
//

#include "Parser.h"
#include "OpenDataServerCmd.h"
#include "ContainerCommand.h"
#include "ConnectCmd.h"

queue<ICommand*> Parser::Parse(queue<string> tokens) {
    queue<ICommand*> commands;
    while (!tokens.empty()) {
        Commands id = GetCommandId(tokens);
        if (IsContainer(id))
            commands.push(CreateContainerCmd(tokens, id));
        else
            commands.push(CreateCommand(tokens, id));
        TrimEndline(tokens);
    }
    return commands;
}

Commands Parser::GetCommandId(queue<string> &tokens) {
    Commands id = IdentifyCommand(tokens.front());
    if (id != SET_VAR)
        tokens.pop();
    return id;
}

ICommand* Parser::CreateContainerCmd(queue<string> &tokens, Commands id) {
    ContainerCommand *container;
    switch (id) {
        case WHILE:
            container = new LoopCommand(ExtractExpression(tokens));
            break;
        case IF:
            container = new IfCommand(ExtractExpression(tokens));
            break;
        default:
            perror(CMD_ID_ERROR);
            return nullptr;
    }
    while (tokens.front() == "{" || tokens.front() == "\n") {
        tokens.pop();
    }
    while (tokens.front() != "}") {
        Commands innerId = GetCommandId(tokens);
        if (IsContainer(id))
            container->AddCommand(CreateContainerCmd(tokens, innerId));
        else
            container->AddCommand(CreateCommand(tokens, innerId));
        TrimEndline(tokens);
    }
    tokens.pop();
    return container;
}

ICommand* Parser::CreateCommand(queue<string> &tokens, Commands id) {
    string varName;
    switch(id) {
        case SET_VAR: {
            varName = ExtractToken(tokens);
            if (ExtractToken(tokens) != "=")
                perror(SYNTAX_ERROR);
            return new UpdateVarCmd(manager, varName, ExtractExpression(tokens));
        }
        case OPEN_DATA_SERVER: {
            IExpression *port = ExtractExpression(tokens);
            IExpression *hz = ExtractExpression(tokens);
            return new OpenDataServerCmd(manager, port, hz);
        }
        case CONNECT: {
            string ip = ExtractToken(tokens);
            IExpression *port = ExtractExpression(tokens);
            return new ConnectCmd(manager, ip, port);
        }
        case PRINT: {
            if (IsString(tokens.front()))
                return new PrintStrCmd(ExtractToken(tokens));
            else
                return new PrintExpCmd(ExtractExpression(tokens));
        }
        case SLEEP: {
            return new SleepCmd(ExtractExpression(tokens));
        }
        case DEFINE_VAR: {
            varName = ExtractToken(tokens);
            if (ExtractToken(tokens) != "=")
                perror(SYNTAX_ERROR);
            if (tokens.front() != "bind")
                return new DefineVarCmd(manager, varName, ExtractExpression(tokens));
            else {
                tokens.pop();
                return new DefineVarCmd(manager, varName, ExtractToken(tokens));
            }
        }
        default: {
            perror(CMD_ID_ERROR);
            return nullptr;
        }
    }
}

IExpression* Parser::ExtractExpression(queue<string> &tokens) {
    queue<string> rawExpression;
    do {
        rawExpression.push(ExtractToken(tokens));
    } while (IsWithinExpression(rawExpression.back(), tokens));
    return ShuntingYard(rawExpression);
}

bool Parser::IsString(string token) const { return token[0] == '\"'; }

void Parser::TrimEndline(queue<string> &tokens) {
    while (tokens.front() == "\n")
        tokens.pop();
}

bool Parser::IsWithinExpression(string previousToken, queue<string> tokens) {
    string nextToken = tokens.front();
    if ((nextToken == "\n") || (nextToken == "{") || (nextToken == "}"))
        return false;
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
