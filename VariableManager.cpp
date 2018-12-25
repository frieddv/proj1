//
// Created by ariel on 12/21/18.
//

#include "VariableManager.h"

void VariableManager::bindToLocal(string varName, string target) {
    if (boundVars.count(target)) {
        boundVars[varName] = boundVars[target];
        return;
    }
    varToSource[varName] = varToSource[target];
}

void VariableManager::bindVar(string varName, string target) {
    if (target[0] == '\"') {
        bindToServer(varName, target);
        return;
    }
    bindToLocal(varName, target);
}

double VariableManager::getVarValue(string varName) {
    if (boundVars.count(varName))
        return getValueFromServer(boundVars[varName]);
    string local = varToSource[varName];
    return localVars[local];
}

void VariableManager::setVarValue(string varName, double value) {
    if (boundVars.count(varName)) {
        setValueOnServer(boundVars[varName], value);
        return;
    }
    string local = varToSource[varName];
    localVars[local] = value;

}

bool VariableManager::doesVarExist(string varName) {
    return (varToSource.count(varName)) || (boundVars.count(varName));
}

void VariableManager::addLocalVar(string varName, double value) {
    localVars[varName] = value;
    varToSource[varName] = varName;
}

void VariableManager::setValueOnServer(string path, double value) {
implement this!!!
}

double VariableManager::getValueFromServer(string path) {
implement this as well!!!
}

void VariableManager::setIndices(string path, int index) {
    pathesToIndices[path] = index;
}