//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_UNARYEXP_H
#define PROJ1_UNARYEXP_H


#include "IExpression.h"

class UnaryExp : IExpression{
public:
    virtual double calculate() = 0;
};


#endif //PROJ1_UNARYEXP_H
