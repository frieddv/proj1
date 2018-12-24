//
// Created by ariel on 12/24/18.
//

#ifndef PROJ1_PARSER_H
#define PROJ1_PARSER_H

#include <queue>
#include <stack>
#include "ICommand.h"

enum Commands { VarCmd, OpenDataServerCmd, ConnectCmd, PrintCmd, WhileCmd, IfCmd, SleepCmd, DefineCmd };
enum SignOp {AND, OR, BIGGER, SMALLER, EQUAL, NOTEQUAL, BIGEQUAL, SMALLEQUAL, PLUS, MINUS, NEG, MULT, DIV};

class Parser {
private:
    ICommand *CreateCommand(queue<string> &tokens);
    ICommand *CreateContainerCmd(queue<string> &tokens);
    string ExtractToken(queue<string> &tokens);
    Commands IdentifyCommand(string firstToken);
    bool IsNumber(string token);
    SignOp WhatSign(string sign);
    int GetPrecedence(string op);
    IExpression* ApplyOp(string op, IExpression *left, IExpression *right);
    string ExtractStrFromStack(stack<string> stack);
    IExpression* ExtractExpFromStack(stack<IExpression*> stack);
    void ShuntingYard(queue<string> tokens);

public:
    vector<ICommand*> Parse(queue<string> tokens);
};


#endif //PROJ1_PARSER_H
