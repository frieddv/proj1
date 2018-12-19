//
// Created by frieddv on 12/18/18.
//

#include "Lexer.h"

vector<string> Lexer::lex(istream buffer) {
    char line[MAX_LINE_LENGTH] = {0};
    vector<string> tokens;
    smatch match;
    while (!buffer.eof()) {
        buffer.getline(line, MAX_LINE_LENGTH);
        string temp = line;
        while (!(temp.empty())) {
            temp = trimLeadingWhitespace(temp);
            if (regex_search(temp, match, word,regex_constants::match_continuous)) {
                temp = trimToken(temp, (unsigned long)match.length(), tokens);
                tokens.push_back(temp.substr(0, (unsigned long)match.length()));
                temp = temp.substr((unsigned long)(match.length()));
            }
        }
        tokens.emplace_back("\n");
    }

    return tokens;
}

string Lexer::trimToken(string line, unsigned long tokenLength,
                        vector<string> &tokens) {
    tokens.push_back(line.substr(0, tokenLength));
    return line.substr(tokenLength);
}

string Lexer::trimLeadingWhitespace(string line) {
    smatch match;
    if (regex_search(line, match, whitespace, regex_constants::match_continuous))
        return line.substr((unsigned long)match.length());
    return line;
}
