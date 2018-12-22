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
    map<string, string> boundToServer;
    multimap<string, string> boundToLocal;

    void bindToServer(string varName, string path) {boundToServer[varName] = path;}

    void bindToLocal(string varName, string target);

    string getVarSource(string varName, vector<string> alreadySearched);

    bool wasAlreadySearched(string varName, vector<string> alreadySearched);

    vector<string> getLocalBindings(string varName);

public:
    void addLocalVar(string varName, double value) {localVars[varName] = value;}

    void bindVar(string varName, string target);

    double getVarValue(string varName);

    void setVarValue(string varName, double value);
};


#endif //PROJ1_VARIABLEMANAGER_H
