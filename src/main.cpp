#include "CLI.h"

int main(int argc, char** argv) {
    ParseKey parser;
    try {
        parser.parse_flag(argc, argv);
    }
    catch (KeyException &e){
        std::cerr << "A key exception occurred (" << e.what_exception() << ")\n";
    }
    return 0;
}

