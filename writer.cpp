#include "writer.h"

void writer::function_write(lexer &lex) {
    std::ofstream main("main.txt");
    if (!main.is_open())
        exit(1);
    main << lex.return_type[0] << " " << lex.fun_name[0]<< "(" << lex.fun_args[0]
    << ")" << " " << "{" << std::endl << "\t" << "return" << " "
    << lex.return_var[0] << " " << "}" << std::endl;
    main.close();
}
