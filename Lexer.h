//
// Created by frieddv on 12/18/18.
//

#ifndef PROJ1_LEXER_H
#define PROJ1_LEXER_H

#include <regex>

#define WORDPAT "[a-zA-Z][a-zA-Z0-9]*"
#define NUMBERPAT "-?(([1-9][0-9]*)|0)(\.[0-9]+)?"
#define IPPAT "(([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|[25[0-5])\.){3}([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|[25[0-5])"
#define SERVERPATH "\"[^\"]+\""
#define DUALOPERATOR "(!=)|(==)|(<=)|(>=)"
#define SINGLEOPERATOR "[=\-*/()=={}<>]"
#define MAX_LINE_LENGTH 1024

using namespace std;

class Lexer {

private:

    regex word;
    regex IP;
    regex number;
    regex serverPath;
    regex dualOp;
    regex singleOp;

public:
    Lexer() : word(WORDPAT), IP(IPPAT), number(NUMBERPAT),
            serverPath(SERVERPATH), dualOp(DUALOPERATOR),
            singleOp(SINGLEOPERATOR) {};

    vector<string> lex (istream buffer);
};


#endif //PROJ1_LEXER_H
