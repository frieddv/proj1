//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_LESSTHAN_H
#define PROJ1_LESSTHAN_H


#include "ComparisonCondition.h"

class LessThan : public ComparisonCondition{
public:

    bool evaluate() {
        return left->calculate() < right->calculate();
    }
};


#endif //PROJ1_LESSTHAN_H
