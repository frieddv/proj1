//
// Created by frieddv on 12/18/18.
//

#ifndef PROJ1_ICOMMAND_H
#define PROJ1_ICOMMAND_H


#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>
#include "ICondition.h"
#include "IExpression.h"

using namespace std;

class ICommand {
public:
    virtual void doCommand() = 0;
};

class ContainerCommands : public ICommand {
protected:
    ICondition *condition;

public:
    ContainerCommands(std::vector<std::string> info);
};
class PrintExpCmd : public ICommand {
private:
    IExpression *exp;
public:
    PrintExpCmd(IExpression *exp) : exp(exp) {};
    void doCommand () { cout << exp->calculate();}
    virtual ~PrintExpCmd() { delete exp;}
};
class PrintStrCmd : public ICommand {
private:
    string str;
public:
    PrintStrCmd(string str) {this->str = str.substr(1, str.length() - 2);}
    void doCommand() {cout << str;}
};
class SleepCmd : public ICommand {
private:
    IExpression *exp;
public:
    SleepCmd(IExpression *exp) : exp(exp) {};
    void doCommand() {this_thread::sleep_for(chrono::milliseconds((int)exp->calculate()));}
};

class DefineVarCmd : public ICommand {
private:
    map<string, double> *localVars;
    map<string, string> *boundToServer;
    map<string, string> *boundToLocals;
    string varName;
    string bindTarget;
    IExpression *exp;
public:
    DefineVarCmd(map<string, double> *localVars, map<string, string> *boundToServer, map<string, string> *boundToLocals,
                 const string &varName, const string &bindTarget) : localVars(localVars), boundToServer(boundToServer),
                                                                    boundToLocals(boundToLocals), varName(varName),
                                                                    bindTarget(bindTarget), exp(nullptr) {};

    DefineVarCmd(map<string, double> *localVars, map<string, string> *boundToServer, map<string, string> *boundToLocals,
                 const string &varName, IExpression *exp) : localVars(localVars), boundToServer(boundToServer),
                                                            boundToLocals(boundToLocals), varName(varName),
                                                            bindTarget(""), exp(exp) {};
    void doCommand();
};
#endif //PROJ1_ICOMMAND_H
