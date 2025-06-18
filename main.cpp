#include <cstdio>
#include <string>
#include <fstream>
#include "lexer.h"
#include "writer.h"
#include <iostream>

int main() {
    FILE *f = fopen("lex.txt", "r");
    if (!f) {
        perror("Failed to open file");
        return 1;
    }

    lexer lex;

    int tok;
    std::cout << "Lexing" << std::endl;
    while (lex.gettok(f)!= tok_eof) {
        // if (tok == tok_identifier)
        //     printf("Identifier: %s\n", lex.IdentifierStr.c_str());
        // else if (tok == tok_number)
        //     printf("Number: %f\n", lex.NumberVal);
        // else
        //     printf("Token: %d\n", tok);
    }
    // for (auto s : lex.var_name) {
    //     printf("var: %s\n", s.c_str());
    // }
    // if (lex.var_type.empty()) std::cout << "empty" << std::endl;
    // for (auto s : lex.var_type) {
    //     printf("type: %s\n", s.c_str());
    // }
    //
    // for (auto s : lex.var_value) {
    //     printf("value: %s\n", s.c_str());
    // }
    //
    // for (auto s : lex.fun_args) {
    //     printf("args: %s\n", s.c_str());
    // }

    for (auto x : lex.count) {
        std::cout << x.first << ":" << x.second << std::endl;
    }

    writer w;
    w.function_write(lex);

    fclose(f);
    return 0;
}
