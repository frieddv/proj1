//
// Created by frieddv on 12/17/18.
//
#ifndef PROJ1_DIVISION_H
#define PROJ1_DIVISION_H

#include "BinaryExp.h"
#include <stdexcept>

class Division : public BinaryExp {

    double calculate() {
        if (right->calculate() == 0) {
            throw std::logic_error("Divide by zero exception");
        }
        return left->calculate() / right->calculate();
    }
};


#endif //PROJ1_DIVISION_H
