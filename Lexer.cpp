//
// Created by frieddv on 12/18/18.
//

#include "Lexer.h"

vector<string> Lexer::lex(istream buffer) {
    char line[MAX_LINE_LENGTH] = {0};
    vector<string> tokens;
    while (!buffer.eof()) {
        buffer.getline(line, MAX_LINE_LENGTH);
        string temp = line;
        while (!(temp.empty())) {
            if ()
        }
    }

    return tokens;
}
