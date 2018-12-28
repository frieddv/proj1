//
// Created by ariel on 12/21/18.
//

#include "VariableManager.h"

void VariableManager::BindToLocal(string varName, string target) {
    if (boundVars.count(target)) {
        boundVars[varName] = boundVars[target];
        return;
    }
    varToSource[varName] = varToSource[target];
}

void VariableManager::BindVar(string varName, string target) {
    if (target[0] == '\"') {
        BindToServer(varName, target);
        return;
    }
    BindToLocal(varName, target);
}

double VariableManager::GetVarValue(string varName) {
    if (boundVars.count(varName))
        return GetValueFromServer(boundVars[varName]);
    string local = varToSource[varName];
    return localVars[local];
}

void VariableManager::SetVarValue(string varName, double value) {
    if (boundVars.count(varName)) {
        SetValueOnServer(boundVars[varName], value);
        return;
    }
    string local = varToSource[varName];
    localVars[local] = value;

}

bool VariableManager::DoesVarExist(string varName) {
    return existingVars.count(varName) > 0;
}

void VariableManager::AddLocalVar(string varName, double value) {
    localVars[varName] = value;
    varToSource[varName] = varName;
}

void VariableManager::SetValueOnServer(string path, double value) {
    pendingUpdates.push(make_pair(path.substr(1, path.length() - 2), value));
}

double VariableManager::GetValueFromServer(string path) {
    string corePath = path.substr(1, path.length() - 2);
    return pathsToXml[corePath];
}

void VariableManager::SetIndices(string path, double index) {
    pathsToXml[path] = index;
}

pair<string, double> VariableManager::PopPendingUpdate() {
    pair<string, double> nextUpdate = pendingUpdates.front();
    pendingUpdates.pop();
    return nextUpdate;
}
