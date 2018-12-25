//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_SEGREGATIONCONDITION_H
#define PROJ1_SEGREGATIONCONDITION_H


#include "ICondition.h"

class AggregationCondition : public ICondition {
protected:
    IExpression *lhs;
    IExpression *rhs;
public:
    AggregationCondition(IExpression *left, IExpression *right) : lhs(left), rhs(right) {}
    virtual bool Evaluate() = 0;
};

class OrCondition : public AggregationCondition {
public:
    OrCondition(IExpression *left, IExpression *right) : AggregationCondition(left, right) {}
    bool Evaluate() {return lhs->Calculate() || rhs->Calculate();}
};

class AndCondition : public AggregationCondition {
public:
    AndCondition(IExpression *left, IExpression *right) : AggregationCondition(left, right) {}
    bool Evaluate() { return lhs->Calculate() && rhs->Calculate();}
};
#endif //PROJ1_SEGREGATIONCONDITION_H
