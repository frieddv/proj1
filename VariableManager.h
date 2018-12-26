//
// Created by ariel on 12/21/18.
//

#ifndef PROJ1_VARIABLEMANAGER_H
#define PROJ1_VARIABLEMANAGER_H

#include <map>
#include <queue>

using namespace std;

enum ThreadId {MAIN, SERVER, CLIENT};

class VariableManager {
private:
    map<string, double> localVars;
    map<string, string> boundVars;
    map<string, string> varToSource;
    map<string, double> pathsToXml;
    queue<pair<string, double>> pendingUpdates;
    map<ThreadId, bool> isThreadDone = {{MAIN, false}, {SERVER, true}, {CLIENT, true}};
    bool isConnected = false;

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

    void ThreadStarted(ThreadId id) { isThreadDone[id] = false; }

    void ThreadFinished(ThreadId id) { isThreadDone[id] = true; }

    bool isThreadFinished(ThreadId id) { return isThreadDone[id]; }

    void ConnectedToServer() { isConnected = true; }

    bool IsConnected() { return isConnected; }

    bool IsUpdatePending() { return !pendingUpdates.empty(); }

    pair<string, double> PopPendingUpdate();
};


#endif //PROJ1_VARIABLEMANAGER_H
