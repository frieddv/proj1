#include <iostream>
#include <fstream>
#include "Lexer.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) //must give a file name
        return -1;
    ifstream script(argv[1], ios::in);
    if (!script.is_open()) {
        return -1;
    }
    Lexer *lexer = new Lexer();
    queue<string> tokens = lexer->Lex(script);

    std::cout << "Hello, World!" << std::endl;

    delete lexer;
    script.close();
    return 0;
}