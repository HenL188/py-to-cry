#pragma once
#include <fstream>
#include "lexer.h"
class writer {
    static void debug(lexer &lex);
    void main_write(lexer &lex, int i, int j);
    std::ofstream main;
    int i;
    public:
   void function_write(lexer& lex);
    writer();
};


