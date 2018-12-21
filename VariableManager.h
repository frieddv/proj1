//
// Created by ariel on 12/21/18.
//

#ifndef PROJ1_VARIABLEMANAGER_H
#define PROJ1_VARIABLEMANAGER_H

#include <string>
#include <map>

using namespace std;

class VariableManager {
private:
    map<string, double> localVars;
    map<string, string> boundVars;

public:
    void addLocalVar(string name, double value);
};


#endif //PROJ1_VARIABLEMANAGER_H
