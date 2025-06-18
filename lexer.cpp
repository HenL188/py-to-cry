#include "lexer.h"
#include <cctype>
#include <cstdio>
#include <string>
#include <iostream>

lexer::lexer() {
    func_count = 0;
    var_count = 0;
}

int lexer::gettok(FILE *f) {
    static int LastChar = ' ';

    while (isspace(LastChar))
        LastChar = fgetc(f);

    // Identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(LastChar) || LastChar == '_') {
        IdentifierStr = LastChar; // Store the first character
        while (isalnum(LastChar = fgetc(f)))
            IdentifierStr += LastChar;
        if (IdentifierStr == "def") {
            if (var_count > 0) var_count = 0;
            func_count += 1;
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
            IdentifierStr.clear();
            LastChar = fgetc(f);
            if (LastChar == ':') {
                return_type.emplace_back("void");
                return_var.emplace_back(" ");
            }
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
            return tok_return;
        }
        var_name.push_back(IdentifierStr);
        var_count += 1;
        if (func_count == 0) count[0] = var_count;
        if (func_count > 0) count[func_count] = var_count;
        return tok_identifier;
    }
    if (LastChar == '=') {
        LastChar = fgetc(f);
        while (isspace(LastChar))
            LastChar = fgetc(f);
        if (isdigit(LastChar) || LastChar == '.') {
            bool type_float = false;
            std::string NumStr; // Buffer for the number string
            do {
                NumStr += LastChar;
                LastChar = fgetc(f);
                if (LastChar == '.') {
                    type_float = true;
                }
            } while (isdigit(LastChar) || LastChar == '.');
            if (type_float == true) {
                var_type.emplace_back("float");
            }else {
                var_type.emplace_back("int");
            }
            var_value.push_back(NumStr);
        }
        // LastChar = fgetc(f);
        switch (LastChar) {
            case 34:
                IdentifierStr = LastChar; // Store the first character
                while (isalnum(LastChar = fgetc(f)))
                    IdentifierStr += LastChar;
                var_type.emplace_back("const char*");
                IdentifierStr += 34;
                var_value.push_back(IdentifierStr);
                break;
            case 39:
                IdentifierStr = LastChar; // Store the first character
                while (isalnum(LastChar = fgetc(f)))
                    IdentifierStr += LastChar;
                var_type.emplace_back("char");
                IdentifierStr += 39;
                var_value.push_back(IdentifierStr);
                break;
            default:
                break;
        }
        LastChar = fgetc(f);
        return tok_equal;
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
