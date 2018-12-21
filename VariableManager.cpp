//
// Created by ariel on 12/21/18.
//

#include <algorithm>
#include "VariableManager.h"

void VariableManager::bindToLocal(string varName, string target) {
    if (boundVars.count(target)) {
        boundVars[varName] = boundVars[target];
        return;
    }
    boundToLocal.insert(make_pair(varName, target));
    boundToLocal.insert(make_pair(target, varName));
}

void VariableManager::bindVar(string varName, string target) {
    if (target[0] == '\"') {
        bindToServer(varName, target);
        return;
    }
    bindToLocal(varName, target);
}

double VariableManager::getVarValue(string varName) {
    if (localVars.count(varName))
        return localVars[varName];
    if (boundVars.count(varName))
        return getValueFromServer(boundVars[varName]); //separate object?
    return searchInLocalBindingMap(varName, vector<string>());
}

void VariableManager::setVarValue(string varName, double value) {
    if (trySetVar(varName, value))
        return;
    vector<string> alreadySearched = vector<string>();
    setValueToLocalBinding(varName, alreadySearched, value);
}

void VariableManager::setValueToLocalBinding(string varName,
                                             vector<string> &alreadySearched,
                                             double value) {
    alreadySearched.push_back(varName);
    if (localVars.count(varName)) {
        localVars[varName] = value;
        return;
    }
    if (boundVars)
}

double VariableManager::searchInLocalBinding(string varName,
                                             vector<string> alreadySearched) {
    return 0;
}

bool VariableManager::trySetVar(string varName, double value) {
    if (localVars.count(varName)) {
        localVars[varName] = value;
        return true;
    }
    if (boundVars.count(varName)) {
        setValueOnServer(boundVars[varName], value); //same separate object?
        return true;
    }
    return false;
}

string VariableManager::getVarSource(string varName,
                                    vector<string> alreadyChecked) {
    if ((localVars.count(varName)) || (boundVars.count(varName)))
        return varName;
    if (wasAlreadySearched(varName, alreadyChecked))
        throw logic_error("stop this local binding check loop");
    alreadyChecked.push_back(varName);

}

bool VariableManager::wasAlreadySearched(string varName,
                                         vector<string> alreadySearched) {
    auto index = find(alreadySearched.begin(), alreadySearched.end(), varName);
    return index != alreadySearched.end();
}
