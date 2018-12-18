//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_COMPARISONCONDITION_H
#define PROJ1_COMPARISONCONDITION_H


#include "ICondition.h"
#include "IExpression.h"

class ComparisonCondition : public ICondition {
protected:
    IExpression *left;
    IExpression *right;

public:

    ComparisonCondition(IExpression *left, IExpression *right) : left(left), right(right) {};

    virtual bool evaluate() = 0;
};


#endif //PROJ1_COMPARISONCONDITION_H
