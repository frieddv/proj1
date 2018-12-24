//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_IEXPRESSION_H
#define PROJ1_IEXPRESSION_H


class IExpression {

public:
    virtual double calculate() = 0;

    virtual ~IExpression() = 0;
};


#endif //PROJ1_IEXPRESSION_H
