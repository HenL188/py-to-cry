#include "writer.h"
#include <iostream>

#ifndef NDEBUG
void writer::debug(lexer &lex) {
    if (lex.fun_name.size() != lex.return_type.size() || lex.fun_name.size() != lex.fun_args.size()) {
        std::cerr << "Mismatch in function definition arrays sizes!" << std::endl;
        exit(1);
    }
    if (lex.var_name.size() != lex.var_type.size() || lex.var_name.size() != lex.var_value.size()) {
        std::cerr << "Mismatch in variable arrays sizes!" << std::endl;
        exit(1);
    }
}
#endif

void writer::function_write(lexer &lex) {
    std::ofstream main("main.txt");
    if (!main.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        exit(1);
    }
    debug(lex);
    int j = 0;
    for (int k = 0; k < lex.count[0]; k++) {
        main << lex.var_type[j] << " " << lex.var_name[j] << " = " << lex.var_value[j] << ";" << std::endl;
        j++;
    }
    for (int i = 0; i < lex.fun_name.size(); i++) {

        if (lex.return_type[i] == "void") {

            main << lex.return_type[i] << " " << lex.fun_name[i] << "(" << lex.fun_args[i] << ") {" << std::endl;
            debug(lex);
            for (int k = 0; k < lex.count[i + 1]; k++) {
                main << "\t" << lex.var_type[j] << " " << lex.var_name[j] << " = " << lex.var_value[j] << ";" << std::endl;
                j++;
            }
            main << "}" << std::endl;
        }
        else if (lex.return_type[i] == "char") {
            main << lex.return_type[i] << " " << lex.fun_name[i] << "(" << lex.fun_args[i] << ") {" << std::endl;
            debug(lex);
            for (int k = 0; k < lex.count[i + 1]; k++) {
                main << "\t" << lex.var_type[j] << " " << lex.var_name[j] << " = " << lex.var_value[j] << ";" << std::endl;
                j++;
            }
            main << "\treturn " << lex.return_var[i] << ";" << std::endl;
            main << "}" << std::endl;
        }else {
            main << lex.return_type[i] << " " << lex.fun_name[i] << "(" << lex.fun_args[i] << ") {" << std::endl;
            debug(lex);
            for (int k = 0; k < lex.count[i + 1]; k++) {
                main << "\t" << lex.var_type[j] << " " << lex.var_name[j] << " = " << lex.var_value[j] << ";" << std::endl;
                j++;
            }
            main << "\treturn " << lex.return_var[i] << ";" << std::endl;
            main << "}" << std::endl;
        }

    }

    main.close();
}
