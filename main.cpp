#include <stdio.h>
#include <string>
#include <fstream>
#include "lexer.h"

int main() {
    FILE *f = fopen("lex.txt", "r");
    if (!f) {
        perror("Failed to open file");
        return 1;
    }

    lexer lex;

    int tok;
    while ((tok = lex.gettok(f)) != tok_eof) {
        if (tok == tok_identifier)
            printf("Identifier: %s\n", lex.IdentifierStr.c_str());
        else if (tok == tok_number)
            printf("Number: %f\n", lex.NumberVal);
        else
            printf("Token: %d\n", tok);
    }
    // for (auto s : fun_name) {
    //     printf("%s\n", s.c_str());
    // }
    // for (auto s : fun_args) {
    //     printf("%s\n", s.c_str());
    // }
    // for (auto s : return_type) {
    //     printf("%s\n", s.c_str());
    // }
    // for (auto s : return_var) {
    //     printf("%s\n", s.c_str());
    // }


    fclose(f);
    return 0;
}
