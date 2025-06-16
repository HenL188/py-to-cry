#include "writer.h"

void writer::function_write(lexer &lex) {
    std::ofstream main("main.txt");
    if (!main.is_open())
        exit(1);
    for (int i = 0; i < lex.fun_name.size(); i++) {
        if (lex.return_type[i] == "void") {
            main << lex.return_type[i] << " " << lex.fun_name[i]<< "(" << lex.fun_args[i]
            << ")" << " " << "{" << std::endl;
            for (int i = 0; i < lex.var_name.size(); i++) {
                main << "\t" << ";" << std::endl << " " << "}" << std::endl << lex.var_type[i] << " " << lex.var_name[i] << " " << "=" << " " << lex.var_value[i];
            }
        }
        else {
            main << lex.return_type[i] << " " << lex.fun_name[i]<< "(" << lex.fun_args[i]
            << ")" << " " << "{" << std::endl << "\t" << "return" << " "
            << lex.return_var[i] << ";" << " " << "}" << std::endl;
        }
    }
    main.close();
}
