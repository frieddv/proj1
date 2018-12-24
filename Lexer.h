//
// Created by frieddv on 12/18/18.
//

#ifndef PROJ1_LEXER_H
#define PROJ1_LEXER_H

#include <regex>
#include <queue>

#define WORD_PAT "[a-zA-Z][a-zA-Z0-9]*"
#define NUMBER_PAT "(([1-9][0-9]*)|0)(\.[0-9]+)?"
#define IP_PAT "(([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|[25[0-5])\.){3}([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|[25[0-5])"
#define STRING "\"[^\"]+\""
#define DUAL_OPERATOR "(!=)|(==)|(<=)|(>=)"
#define SINGLE_OPERATOR "[=\-*/()=={}<>]"
#define DELIMITERS "[\s,]+"
#define MAX_LINE_LENGTH 1024
#define NEWLINE "\n"

using namespace std;

class Lexer {

private:

    regex word;
    regex IP;
    regex number;
    regex stringParam;
    regex dualOp;
    regex singleOp;
    regex delimiters;

    void extractToken(string &line, unsigned long tokenLength,
                        queue<string>& tokens);
    void trimLeadingGarbage(string &line);

    bool lineStartsWith(const string &line, smatch &match,
                        const regex &tokenTemplate) const;

    void tryExtractLeadingToken(string &temp, queue<string> &tokens,
                                const regex &tokenType);

public:
    Lexer() : word(WORD_PAT), IP(IP_PAT), number(NUMBER_PAT),
            stringParam(STRING), dualOp(DUAL_OPERATOR),
            singleOp(SINGLE_OPERATOR), delimiters(DELIMITERS) {}

    queue<string> lex(istream &buffer);
};


#endif //PROJ1_LEXER_H
