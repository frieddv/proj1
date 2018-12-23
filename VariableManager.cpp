//
// Created by ariel on 12/21/18.
//

#include <algorithm>
#include "VariableManager.h"

void VariableManager::bindToLocal(string varName, string target) {
    if (boundToServer.count(target)) {
        boundToServer[varName] = boundToServer[target];
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
    string source = getVarSource(varName, vector<string>());
    if (localVars.count(source))
        return localVars[source];
    return getValueFromServer(boundToServer[varName]); //separate class?
}

void VariableManager::setVarValue(string varName, double value) {
    string source = getVarSource(varName, vector<string>());
    if (localVars.count(source)) {
        localVars[source] = value;
        return;
    }
    setValueOnServer(boundToServer[varName], value); //same separate class?
}

string VariableManager::getVarSource(string varName,
                                    vector<string> alreadyChecked) {
    if ((localVars.count(varName)) || (boundToServer.count(varName)))
        return varName;
    if (wasAlreadySearched(varName, alreadyChecked))
        throw logic_error("stop this local binding check loop");
    alreadyChecked.push_back(varName);
    vector<string> bindings = getLocalBindings(varName);
    for (string binding : bindings) {
        try {
            return getVarSource(binding, alreadyChecked);
        }
        catch (logic_error) {
            continue; //if one binding was a dead end, check the others
        }
    }
    throw logic_error("local binding not found");
}

bool VariableManager::wasAlreadySearched(string varName,
                                         vector<string> alreadySearched) {
    auto index = find(alreadySearched.begin(), alreadySearched.end(), varName);
    return index != alreadySearched.end();
}

vector<string> VariableManager::getLocalBindings(string varName) {
    vector<string> bindings;
    auto iterators = boundToLocal.equal_range(varName);
    for (auto it = iterators.first; it != iterators.second; ++it)
        bindings.push_back(it->second);
    return bindings;
}

bool VariableManager::doesVarExist(string varName) {
    return (boundToLocal.count(varName)) || (boundToServer.count(varName)) ||
            (localVars.count(varName));
}
