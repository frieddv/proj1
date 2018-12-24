//
// Created by frieddv on 12/18/18.
//

#include "Lexer.h"

queue<string> Lexer::lex(istream &buffer) {
    char line[MAX_LINE_LENGTH] = {0};
    queue<string> tokens;
    regex templates[] = {word, IP, number, stringParam, dualOp, singleOp};
    while (!buffer.eof()) {
        buffer.getline(line, MAX_LINE_LENGTH);
        string temp = line;
        while (!(temp.empty())) {
            trimLeadingGarbage(temp);
            for (const regex &r : templates) {
                tryExtractLeadingToken(temp, tokens, r);
            }
        }
        tokens.push(NEWLINE);
    }

    return tokens;
}

void Lexer::tryExtractLeadingToken(string &temp, queue<string> &tokens,
                                const regex &tokenType) {
    smatch match;
    if (lineStartsWith(temp, match, tokenType)) {
                extractToken(temp, (unsigned long)match.length(), tokens);
    }
}

bool Lexer::lineStartsWith(const string &line, smatch &match,
                            const regex &tokenTemplate) const {
    return regex_search(line, match, tokenTemplate, regex_constants::match_continuous);
}

void Lexer::extractToken(string &line, unsigned long tokenLength,
                        queue<string> &tokens) {
    tokens.push(line.substr(0, tokenLength));
    line = line.substr(tokenLength);
}

void Lexer::trimLeadingGarbage(string &line) {
    smatch match;
    if (lineStartsWith(line, match, delimiters))
        line = line.substr((unsigned long)match.length());
}
