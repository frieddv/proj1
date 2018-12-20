//
// Created by frieddv on 12/18/18.
//

#include "Lexer.h"

vector<string> Lexer::lex(istream buffer) {
    char line[MAX_LINE_LENGTH] = {0};
    vector<string> tokens;
    regex templates[] = {word, IP, number, serverPath, dualOp, singleOp};
    while (!buffer.eof()) {
        buffer.getline(line, MAX_LINE_LENGTH);
        string temp = line;
        while (!(temp.empty())) {
            trimLeadingWhitespace(temp);
            for (const regex &r : templates) {
                tryTrimLeadingToken(temp, tokens, r);
            }
        }
        tokens.push_back(NEWLINE);
    }

    return tokens;
}

void Lexer::tryTrimLeadingToken(string &temp, vector<string> &tokens,
                                const regex &tokenType) {
    smatch match;
    if (lineStartsWith(temp, match, tokenType)) {
                trimToken(temp, (unsigned long)match.length(), tokens);
    }
}

bool Lexer::lineStartsWith(const string &line, smatch &match,
                            const regex &tokenTemplate) const {
    return regex_search(line, match, tokenTemplate, regex_constants::match_continuous);
}

void Lexer::trimToken(string &line, unsigned long tokenLength,
                        vector<string> &tokens) {
    tokens.push_back(line.substr(0, tokenLength));
    line = line.substr(tokenLength);
}

void Lexer::trimLeadingWhitespace(string &line) {
    smatch match;
    if (lineStartsWith(line, match, whitespace))
        line = line.substr((unsigned long)match.length());
}
