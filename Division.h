//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_DIVISION_H
#define PROJ1_DIVISION_H


#include "BinaryExp.h"

class Division : BinaryExp {

    double calculate() {
        if (right->calculate() == 0) {
            throw "Cannot divide by zero";
        }
        return left->calculate() / right->calculate();
    }
};


#endif //PROJ1_DIVISION_H
