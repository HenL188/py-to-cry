#pragma once
#include <string>
#include <vector>
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

    // Signs
    tok_plus = -8,
    tok_minus = -9,
    tok_mult = -10,
    tok_div = -11,

    // Conditionals
  tok_if = -13,
  tok_elif = -14,
  tok_else = -15,

    tok_equal = -16,
};

class lexer {
public:
    std::string IdentifierStr;  // Buffer for identifiers
    double NumberVal;         // Holds numeric values
    std::vector<std::string> fun_name ,var_name, var_type, var_value, fun_args, return_type, return_var;
    int gettok(FILE* f);
};
