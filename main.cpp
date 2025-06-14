#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
// Token definitions
enum Token {
    tok_eof = -1,

    // Commands
    tok_def = -2,
    tok_extern = -3,

    // Primary
    tok_identifier = -4,
    tok_number = -5,

    // Syntax
    tok_left_paren = -6,
    tok_right_paren = -7,
    tok_return = -12,

    // Conditionals
    tok_if = -13,
    tok_elif = -14,
    tok_else = -15,

    // Signs
    tok_plus = -8,
    tok_minus = -9,
    tok_mult = -10,
    tok_div = -11,
};

static std::string IdentifierStr;  // Buffer for identifiers
static double NumberVal;         // Holds numeric values
std::vector<std::string> fun_name;
std::vector<std::string> var_name;
std::vector<std::string> fun_args;
std::vector<std::string> return_type;
std::vector<std::string> return_var;
// Function to get the next token
static int gettok(FILE* f) {
    static int LastChar = ' ';

    // Skip whitespace
    while (isspace(LastChar))
        LastChar = fgetc(f);

    // Identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(LastChar)) {
        IdentifierStr = LastChar; // Store the first character
        while (isalnum(LastChar = fgetc(f)))
            IdentifierStr += LastChar;
        if (IdentifierStr == "def") {
            LastChar = fgetc(f);
            IdentifierStr = LastChar;
            while (isalnum(LastChar = fgetc(f)))
                IdentifierStr += LastChar;
            fun_name.push_back(IdentifierStr);
            IdentifierStr.clear();
            while ((LastChar = fgetc(f)) != '(') {
                if (LastChar == ')') break;
                IdentifierStr += LastChar;
            }
            fun_args.push_back(IdentifierStr);
            return tok_def;
        }
        if (IdentifierStr == "extern")
            return tok_extern;
        if (IdentifierStr == "if")
            return tok_if;
        if (IdentifierStr == "elif")
            return tok_elif;
        if (IdentifierStr == "else")
            return tok_else;
        if (IdentifierStr == "return") {
            LastChar = fgetc(f);
            IdentifierStr = LastChar;
            while (isalnum(LastChar = fgetc(f)))
                IdentifierStr += LastChar;
            return_var.push_back(IdentifierStr);
        }

        return tok_identifier;
    }

    // Number: [0-9.]+
    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr; // Buffer for the number string
        do {
            NumStr += LastChar;
            LastChar = fgetc(f);
        } while (isdigit(LastChar) || LastChar == '.');

        NumberVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    // Comment until end of line
    if (LastChar == '#') {
        do
            LastChar = fgetc(f);
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
        if (LastChar != EOF)
            return gettok(f);
    }

    switch (LastChar) {
        case 42:
            LastChar = fgetc(f);
            return tok_mult;
        case 43:
            LastChar = fgetc(f);
            return tok_plus;
        case 45:
            LastChar = fgetc(f);
            if (LastChar == '>') {
                LastChar = fgetc(f);
                IdentifierStr.clear();
                while (isalpha(LastChar = fgetc(f))) {
                    IdentifierStr += LastChar;
                }
                return_type.push_back(IdentifierStr);
                LastChar = fgetc(f);
                return tok_return;
            }
            return tok_minus;
        case 47:
            LastChar = fgetc(f);
            return tok_div;
        default:
            break;
    }

    if (LastChar == ')') {
        LastChar = fgetc(f);
        return tok_right_paren;
    }
    if (LastChar == '(') {
        LastChar = fgetc(f);
        return tok_left_paren;
    }

    // End of file
    if (LastChar == EOF)
        return tok_eof;

    // Otherwise, return the character as its ASCII value
    int ThisChar = LastChar;
    LastChar = fgetc(f);
    return ThisChar;
}

int main() {
    FILE *f = fopen("lex.txt", "r");
    if (!f) {
        perror("Failed to open file");
        return 1;
    }

    int tok;
    while ((tok = gettok(f)) != tok_eof) {
        if (tok == tok_identifier)
            printf("Identifier: %s\n", IdentifierStr.c_str());
        else if (tok == tok_number)
            printf("Number: %f\n", NumberVal);
        else
            printf("Token: %d\n", tok);
    }
    for (auto s : fun_name) {
        printf("%s\n", s.c_str());
    }
    for (auto s : fun_args) {
        printf("%s\n", s.c_str());
    }
    for (auto s : return_type) {
        printf("%s\n", s.c_str());
    }
    for (auto s : return_var) {
        printf("%s\n", s.c_str());
    }

    std::ofstream main("main.txt");
    if (!main.is_open())
        return 1;
    main << return_type[0] << " " << fun_name[0]<< "(" << fun_args[0]
    << ")" << " " << "{" << std::endl << "\t" << "return" << " "
    << return_var[0] << " " << "}" << std::endl;


    fclose(f);
    return 0;
}
