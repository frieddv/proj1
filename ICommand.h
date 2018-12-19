//
// Created by frieddv on 12/18/18.
//

#ifndef PROJ1_ICOMMAND_H
#define PROJ1_ICOMMAND_H


class ICommand {
protected:

    vector<string> tokens;

public:

    ICommand(const vector <string> &tokens) : tokens(tokens) {};

    virtual void doCommand() = 0;
};


#endif //PROJ1_ICOMMAND_H
