#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <exception>
class ParseKey{
private:
    bool encode_flag = false, decode_flag = false;
    std::string input_file, output_file;

public:
    int parse_flag(int argc, char** argv);
    void process();
};

class KeyException: public std::exception{
public:
    explicit KeyException(const std::string& message);
    std::string what_exception();

    std::string message_;
};