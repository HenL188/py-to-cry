#pragma once
#include <fstream>
#include "lexer.h"
class writer {
    static void debug(lexer &lex);
    public:
  static void function_write(lexer& lex);
};


