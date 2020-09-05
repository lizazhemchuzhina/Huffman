#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include <algorithm>
#include "BitReader.h"
#include "BitWriter.h"
#include <queue>

namespace Huffman {
    struct HuffmanNode {
        uint8_t symbol;
        std::unique_ptr<HuffmanNode> left = nullptr, right = nullptr;

        void write_in_tree(BitWriter &b_writer) const;

        void read_in_tree(BitReader &b_reader);
    };// end struct HuffmanNode

    struct frequency {
        int freq;
        uint8_t symbol;

        bool operator<(const frequency &fs) const {
            return (fs.freq < freq);
        }
    };// end struct freq_sym

    class HuffmanTree {
    public:

        HuffmanNode* add_node(const std::vector<bool> &code);

        void write_tree(BitWriter &b_writer) const;

        HuffmanNode &get();

        void read_tree(BitReader &b_reader);

        uint8_t decode_symbol(BitReader &b_reader);

    private:
        HuffmanNode root;
    };//end class HuffmanTree

}//end namespace Huffman
