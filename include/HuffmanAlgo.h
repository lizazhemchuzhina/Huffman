#pragma once

#include <vector>
#include "Huffman.h"

using namespace Huffman;

class HuffmanAlgo {
private:
    std::vector<int> freq_sym;
    std::vector<std::vector<bool>> codes;
    HuffmanTree codes_tree;
    uint32_t symbols_count = 0;

public:
    HuffmanAlgo() : codes(std::vector<std::vector<bool>>(257)),
                    freq_sym(std::vector<int>(256, 0)) {
    }

    void set_frequency(std::istream &is);

    void fill_codes_heap(std::priority_queue<frequency> &codes_heap);

    int calculate_codes_by_heap(std::priority_queue<frequency> &codes_heap, int index = 256);

    void build_codes(std::istream &is);

    std::vector<std::vector<bool>> &get_codes();

    std::vector<int> &get_freq();

    HuffmanTree &get_codes_tree();

    uint32_t &get_symbols_count();

};
