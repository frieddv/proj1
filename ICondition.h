//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_ICONDITION_H
#define PROJ1_ICONDITION_H


#include "IExpression.h"

class ICondition : public IExpression{
public:
    virtual bool Evaluate() = 0;

    virtual double Calculate() { return (int) Evaluate();}
};


#endif //PROJ1_ICONDITION_H
