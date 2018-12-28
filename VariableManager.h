//
// Created by ariel on 12/21/18.
//

#ifndef PROJ1_VARIABLEMANAGER_H
#define PROJ1_VARIABLEMANAGER_H

#include <map>
#include <queue>
#include <set>

using namespace std;

enum ThreadId {MAIN, SERVER, CLIENT};

class VariableManager {
private:
    map<string, double> localVars;
    map<string, string> boundVars;
    map<string, string> varToSource;
    map<string, double> pathsToXml;
    set<string> existingVars;
    queue<pair<string, double>> pendingUpdates;
    map<ThreadId, bool> isThreadDone = {{MAIN, false}, {SERVER, true}, {CLIENT, true}};
    bool isConnected = false;

    void BindToServer(string varName, string path) {boundVars[varName] = path;}

    void BindToLocal(string varName, string target);

    void SetValueOnServer(string path, double value);

    double GetValueFromServer(string path);

public:
    void AddLocalVar(string varName, double value);

    void BindVar(string varName, string target);

    double GetVarValue(string varName);

    void SetVarValue(string varName, double value);

    bool DoesVarExist(string varName);

    void SetIndices(string path, double index);

    void ThreadStarted(ThreadId id) { isThreadDone[id] = false; }

    void ThreadFinished(ThreadId id) { isThreadDone[id] = true; }

    bool IsThreadFinished(ThreadId id) { return isThreadDone[id]; }

    void ConnectedToServer() { isConnected = true; }

    bool IsConnected() { return isConnected; }

    bool IsUpdatePending() { return !pendingUpdates.empty(); }

    void AcknowledgeVar(string varName) { existingVars.insert(varName); }

    pair<string, double> PopPendingUpdate();
};


#endif //PROJ1_VARIABLEMANAGER_H
