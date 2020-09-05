#include "doctest.h"
#include "CLI.h"
#include "HuffmanArchiver.h"


TEST_CASE ("Full encode_decode") {
    std::ofstream ofs("tmp.test");
    std::string testing_str = "I love programming! Ура, ура, ура! Я spent almost 35 часов на Хаффман";
    std::string some_symb = "0-0 ;3 ^.^ @.@";
    ofs << testing_str << '\n' << some_symb;
    ofs.close();

    std::ifstream ifs("tmp.test", std::ios::binary);
    std::ofstream ofs2("tmp2.test", std::ios::binary);

    HuffmanArchiver arch(ifs, ofs2);
    arch.encode(true);

    ifs.close();
    ofs2.close();

    std::ifstream ifs3("tmp2.test", std::ios::binary);
    std::ofstream ofs3("tmp_result.test");

    HuffmanArchiver arch2(ifs3, ofs3);
    arch2.decode(true);

    ifs3.close();
    ofs3.close();

    std::string result;
    std::ifstream ifs4("tmp_result.test");
    getline(ifs4, result);
            CHECK_EQ(testing_str, result);

    getline(ifs4, result);
            CHECK_EQ(result, some_symb);
}