//
// Created by ariel on 12/21/18.
//

#ifndef PROJ1_VARIABLEMANAGER_H
#define PROJ1_VARIABLEMANAGER_H

#include <map>

using namespace std;

class VariableManager {
private:
    map<string, double> localVars;
    map<string, string> boundVars;
    map<string, string> varToSource;
    map<string, double > pathsToXml;

    void bindToServer(string varName, string path) {boundVars[varName] = path;}

    void bindToLocal(string varName, string target);

    void setValueOnServer(string path, double value);

    double getValueFromServer(string path);

public:
    void addLocalVar(string varName, double value);

    void bindVar(string varName, string target);

    double getVarValue(string varName);

    void setVarValue(string varName, double value);

    bool doesVarExist(string varName);

    void setIndices(string path, double index);
};


#endif //PROJ1_VARIABLEMANAGER_H
