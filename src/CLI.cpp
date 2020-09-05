#include "CLI.h"
#include "HuffmanArchiver.h"
#define PLACE() "in file: \"" << __FILE__ << "\", func: \"" << __FUNCTION__ << "\" in line " << __LINE__ << " ==> "

int ParseKey::parse_flag(int argc, char **argv) {
    if (argc != 6) {
        throw KeyException("Invalid number of arguments");
    }

    std::vector<std::string> keys(argc);
    for (int i = 0; i < argc; i++)
        keys[i] = argv[i];

    for (int i = 1; i < argc; i++) {
        if (keys[i] == "-c")
            encode_flag = true;

        if (keys[i] == "-u")
            decode_flag = true;

        if ((keys[i] == "-f" || keys[i] == "--file") && i < argc - 1) {
            input_file = keys[i + 1];
            i++;
        }

        if ((keys[i] == "-o" || keys[i] == "--output") && i < argc - 1) {
            output_file = keys[i + 1];
            i++;
        }
    }

    if (!(encode_flag ^ decode_flag) || input_file.empty() || output_file.empty()) {
        throw KeyException("Wrong flags");
    }
    process();
}

void ParseKey::process() {
    if (encode_flag) {
        std::ifstream ifs;
        std::ofstream ofs;
        ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        try {
            ifs.open(input_file.c_str(), std::ios::binary);
            ofs.open(output_file.c_str(), std::ios::binary);
        } catch (const std::ios_base::failure &e) {
            std::cerr << PLACE() << e.what();
        }

        HuffmanArchiver arch(ifs, ofs);
        arch.encode();
    }

    if (decode_flag) {
        std::ifstream ifs(input_file.c_str(), std::ios::binary);
        std::ofstream ofs(output_file.c_str());
        HuffmanArchiver arch(ifs, ofs);
        arch.decode();
    }
}

KeyException::KeyException(const std::string& message) {
    message_ = message;
}

std::string KeyException::what_exception() {
    return message_;
}
