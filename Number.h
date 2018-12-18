//
// Created by frieddv on 12/17/18.
//

#ifndef PROJ1_NUMBER_H
#define PROJ1_NUMBER_H


#include "UnaryExp.h"

class Number : public UnaryExp {
private:
    double value;
public:

    Number(double value) : value(value) {};

    double calculate() {
        return value;
    }
};


#endif //PROJ1_NUMBER_H
