//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_SEGREGATIONCONDITION_H
#define PROJ1_SEGREGATIONCONDITION_H


#include "ICondition.h"

class AggregationCondition : public ICondition {
protected:
    ICondition *lhs;
    ICondition *rhs;
public:
    AggregationCondition(ICondition *left, ICondition *right) : lhs(left), rhs(right) {}
    virtual bool Evaluate() = 0;
};

class OrCondition : public AggregationCondition {
public:
    OrCondition(ICondition *left, ICondition *right) : AggregationCondition(left, right) {}
    bool Evaluate() {return lhs->Evaluate() || rhs->Evaluate();}
};

class AndCondition : public AggregationCondition {
public:
    AndCondition(ICondition *left, ICondition *right) : AggregationCondition(left, right) {}
    bool Evaluate() { return lhs->Evaluate() && rhs->Evaluate();}
};
#endif //PROJ1_SEGREGATIONCONDITION_H
