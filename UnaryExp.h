//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_UNARYEXP_H
#define PROJ1_UNARYEXP_H

#include "IExpression.h"
#include "VariableManager.h"

using namespace std;

class UnaryExp : public IExpression {
public:
    virtual double Calculate() = 0;

};

class Negation : public UnaryExp {
private:
    IExpression *innerExp;
public:
    Negation(IExpression *innerExp) : innerExp(innerExp) {}
    double Calculate() { return (-1 * innerExp->Calculate());}

    ~Negation() { delete innerExp;}
};

class Number : public UnaryExp {
private:
    double value;
public:
    Number(double value) : value(value) {}
    double Calculate() { return value;}

    ~Number() {};
};

class Var : public UnaryExp{
private:
    string var;
    VariableManager *manager;
public:
    Var(string varName, VariableManager *manager) : var(varName),
                                                    manager(manager){}

    double Calculate() { return manager->GetVarValue(var); }

    ~Var() {};
};

#endif //PROJ1_UNARYEXP_H
