//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_LESSEQUALTHAN_H
#define PROJ1_LESSEQUALTHAN_H


#include "ComparisonCondition.h"

class LessEqualThan : public ComparisonCondition{
public:

    bool evaluate() {
        return left->calculate() <= right->calculate();
    }
};


#endif //PROJ1_LESSEQUALTHAN_H
