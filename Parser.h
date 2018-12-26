//
// Created by ariel on 12/24/18.
//

#ifndef PROJ1_PARSER_H
#define PROJ1_PARSER_H

#include <queue>
#include <stack>
#include "ICommand.h"

#define SYNTAX_ERROR "Syntax Error"

enum Commands { SET_VAR, OPEN_DATA_SERVER, CONNECT, PRINT, WHILE, IF, SLEEP, DEFINE_VAR };
enum SignOp {AND, OR, BIGGER, SMALLER, EQUAL, NOT_EQUAL, BIG_EQUAL, SMALL_EQUAL, PLUS, MINUS, NEG, MULT, DIV, INVALID};

class Parser {
private:
    VariableManager *manager;

    ICommand *CreateCommand(queue<string> &tokens, Commands id);
    ICommand *CreateContainerCmd(queue<string> &tokens, Commands id);
    string ExtractToken(queue<string> &tokens);
    Commands IdentifyCommand(string firstToken);
    bool IsNumber(string token);
    SignOp WhatSign(string sign);
    int GetPrecedence(string op);
    IExpression* ApplyOp(string op, IExpression *left, IExpression *right);
    string ExtractStrFromStack(stack<string> stack);
    IExpression* ExtractExpFromStack(stack<IExpression*> stack);
    IExpression* ShuntingYard(queue<string> &tokens);
    bool IsContainer(Commands id);
    Commands GetCommandId(queue<string> &tokens);
    bool IsWithinExpression(queue<string> tokens);
    bool IsWithinFirstExp(string previousToken, queue<string> tokens);
    IExpression* ExtractExpression(queue<string> &tokens);

public:
    Parser(VariableManager *manager) : manager(manager) {}
    vector<ICommand*> Parse(queue<string> tokens);

    void TrimLeadingEndline(queue<string> &tokens);

    bool IsString(string token) const;
};


#endif //PROJ1_PARSER_H
