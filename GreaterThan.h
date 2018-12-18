//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_GREATERTHAN_H
#define PROJ1_GREATERTHAN_H


#include "ComparisonCondition.h"

class GreaterThan : public ComparisonCondition{
public:

    bool evaluate() {
        return left->calculate() > right->calculate();
    }
};


#endif //PROJ1_GREATERTHAN_H
