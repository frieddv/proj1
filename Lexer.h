//
// Created by frieddv on 12/18/18.
//

#ifndef PROJ1_LEXER_H
#define PROJ1_LEXER_H

#include <regex>

#define WORD_PAT "[a-zA-Z][a-zA-Z0-9]*"
#define NUMBER_PAT "(([1-9][0-9]*)|0)(\.[0-9]+)?"
#define IP_PAT "(([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|[25[0-5])\.){3}([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|[25[0-5])"
#define SERVER_PATH "\"[^\"]+\""
#define DUAL_OPERATOR "(!=)|(==)|(<=)|(>=)"
#define SINGLE_OPERATOR "[=\-*/()=={}<>]"
#define WHITESPACE "[\s,]+"
#define MAX_LINE_LENGTH 1024
#define NEWLINE "\n"

using namespace std;

class Lexer {

private:

    regex word;
    regex IP;
    regex number;
    regex serverPath;
    regex dualOp;
    regex singleOp;
    regex whitespace;

    void trimToken(string &line, unsigned long tokenLength,
                        vector<string>& tokens);
    void trimLeadingWhitespace(string &line);

    bool lineStartsWith(const string &line, smatch &match,
                        const regex &tokenTemplate) const;

    void tryTrimLeadingToken(string &temp, vector<string> &tokens,
                                const regex &tokenType);

public:
    Lexer() : word(WORD_PAT), IP(IP_PAT), number(NUMBER_PAT),
            serverPath(SERVER_PATH), dualOp(DUAL_OPERATOR),
            singleOp(SINGLE_OPERATOR), whitespace(WHITESPACE) {};

    vector<string> lex(istream buffer);
};


#endif //PROJ1_LEXER_H
