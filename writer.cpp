#include "writer.h"

void writer::function_write(lexer &lex) {
    std::ofstream main("main.txt");
    if (!main.is_open())
        exit(1);
    for (int i = 0; i < lex.fun_name.size(); i++) {
        main << lex.return_type[i] << " " << lex.fun_name[i]<< "(" << lex.fun_args[i]
        << ")" << " " << "{" << std::endl << "\t" << "return" << " "
        << lex.return_var[i] << ";" << " " << "}" << std::endl;
    }
    main.close();
}
