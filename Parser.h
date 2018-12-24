//
// Created by ariel on 12/24/18.
//

#ifndef PROJ1_PARSER_H
#define PROJ1_PARSER_H

#include <queue>
#include "ICommand.h"

class Parser {
private:
    ICommand *createCommand(queue<string> &tokens);
    ICommand *createContainer(queue<string> &tokens);
    string popFromQueue(queue<string> &tokens);

public:
    vector<ICommand*> parse(queue<string> tokens);
};


#endif //PROJ1_PARSER_H
