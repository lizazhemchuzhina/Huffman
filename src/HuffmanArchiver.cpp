#include "HuffmanArchiver.h"

void HuffmanArchiver::encode(bool info) {
    BitWriter b_writer(ofs);
    HuffmanAlgo alg;

    alg.build_codes(ifs);

    reset_input_stream();

    if (alg.get_symbols_count() == 0) {
        if (!info)
            std::cout << "0\n0\n0\n";
        return;
    }

    if (!info)
        std::cout << alg.get_symbols_count() << '\n';

    b_writer << alg.get_symbols_count();

    alg.get_codes_tree().write_tree(b_writer);

    int information_bytes_count = b_writer.get_written_bytes();

    write_result(b_writer, alg.get_codes());

    if (!info)
        std::cout << b_writer.get_written_bytes() - information_bytes_count << '\n' << information_bytes_count << '\n';
}

void HuffmanArchiver::write_result(BitWriter &b_writer, const std::vector<std::vector<bool>> &codes) const {
    char c;
    while (ifs.get(c)) {
        for (bool bit : codes[static_cast<uint8_t>(c)]) {
            b_writer << bit;
        }
    }
}

void HuffmanArchiver::reset_input_stream() const {
    ifs.clear();
    ifs.seekg (0, std::ios::beg);
}

void HuffmanArchiver::decode_file_with_tree(HuffmanAlgo &alg, BitReader &b_reader) const {
    int count = alg.get_symbols_count();
    while (count--) {
        ofs << alg.get_codes_tree().decode_symbol(b_reader);
    }
}

void HuffmanArchiver::decode(bool info) {
    BitReader b_reader(ifs);
    HuffmanAlgo alg;

    b_reader >> alg.get_symbols_count();


    alg.get_codes_tree().read_tree(b_reader);

    int information_bytes_count = b_reader.get_read_bytes();
    int output_bytes_count = alg.get_symbols_count();

    decode_file_with_tree(alg, b_reader);

    int data_bytes_count = b_reader.get_read_bytes() - information_bytes_count;
    if (!info)
        std::cout << data_bytes_count << '\n' << output_bytes_count << '\n' << information_bytes_count << '\n';

}
