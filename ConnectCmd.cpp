//
// Created by frieddv on 12/26/18.
//

#include "ConnectCmd.h"

ConnectCmd::ConnectCmd(IExpression *port, const string &IP, VariableManager *variableManager) : port(port), IP(IP),
                                                                                                variableManager(
                                                                                                        variableManager) {}

void ConnectCmd::DoCommand() {

}
