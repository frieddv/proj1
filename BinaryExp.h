//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_BINARYEXP_H
#define PROJ1_BINARYEXP_H


#include "IExpression.h"

class BinaryExp : IExpression {
protected:

    IExpression *left;
    IExpression *right;

public:

    virtual double calculate() = 0;

    BinaryExp(IExpression *a, IExpression *b) : left(a), right(b) {};
};


#endif //PROJ1_BINARYEXP_H
