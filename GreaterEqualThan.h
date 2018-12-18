//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_GREATEREQUALTHAN_H
#define PROJ1_GREATEREQUALTHAN_H


#include "ComparisonCondition.h"

class GreaterEqualThan : public ComparisonCondition{
public:

    bool evaluate() {
        return left->calculate() >= right->calculate();
    }
};


#endif //PROJ1_GREATEREQUALTHAN_H
