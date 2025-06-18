#include "writer.h"
#include <iostream>

void writer::function_write(lexer &lex) {
    std::ofstream main("main.txt");
    if (!main.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        exit(1);
    }

    if (lex.fun_name.size() != lex.return_type.size() || lex.fun_name.size() != lex.fun_args.size()) {
        std::cerr << "Mismatch in function definition arrays sizes!" << std::endl;
        exit(1);
    }

    for (int i = 0; i < lex.fun_name.size(); i++) {
        if (lex.return_type[i] == "void") {
            main << lex.return_type[i] << " " << lex.fun_name[i] << "(" << lex.fun_args[i] << ") {" << std::endl;
            if (lex.var_name.size() != lex.var_type.size() || lex.var_name.size() != lex.var_value.size()) {
                std::cerr << "Mismatch in variable arrays sizes!" << std::endl;
                exit(1);
            }
            for (int j = 0; j < lex.var_name.size();) {
                main << "\t" << lex.var_type[j] << " " << lex.var_name[j] << " = " << lex.var_value[j] << ";" << std::endl;
                lex.var_name.erase(lex.var_name.begin() + j);
                lex.var_type.erase(lex.var_type.begin() + j);
                lex.var_value.erase(lex.var_value.begin() + j);
            }
            main << "}" << std::endl;
        } else {
            main << lex.return_type[i] << " " << lex.fun_name[i] << "(" << lex.fun_args[i] << ") {" << std::endl;
            main << "\treturn " << lex.return_var[i] << ";" << std::endl;
            main << "}" << std::endl;
        }
    }

    main.close();
}
