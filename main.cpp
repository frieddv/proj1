#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) //must give a file name
        return -1;
    ifstream script(argv[1], ios::in);
    if (!script.is_open()) {
        return -1;
    }
    Lexer *lexer = new Lexer();
    VariableManager *varMgr = new VariableManager();
    Parser *parser = new Parser(varMgr);
    queue<string> tokens = lexer->Lex(script);
    vector<ICommand*> commands = parser->Parse(tokens);

    for (ICommand *c : commands) {
        c->DoCommand();
        delete c;
    }

    delete parser;
    delete varMgr;
    delete lexer;
    script.close();
    return 0;
}