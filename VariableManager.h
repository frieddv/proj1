//
// Created by ariel on 12/21/18.
//

#ifndef PROJ1_VARIABLEMANAGER_H
#define PROJ1_VARIABLEMANAGER_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class VariableManager {
private:
    map<string, double> localVars;
    map<string, string> boundVars;
    multimap<string, string> boundToLocal;

    void bindToServer(string varName, string path) {boundVars[varName] = path;}

    void bindToLocal(string varName, string target);

    double searchInLocalBinding(string varName, vector<string> alreadySearched);

    void setValueToLocalBinding(string varName, vector<string> &alreadySearched,
                                double value);

    bool trySetVar(string varName, double value);

    string getVarSource(string varName, vector<string> alreadySearched);

    bool wasAlreadySearched(string varName, vector<string> alreadySearched);

public:
    void addLocalVar(string varName, double value) {localVars[varName] = value;}

    void bindVar(string varName, string target);

    double getVarValue(string varName);

    void setVarValue(string varName, double value);
};


#endif //PROJ1_VARIABLEMANAGER_H
