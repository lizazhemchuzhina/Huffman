
#include "Huffman.h"

#define PLACE() "in file: \"" << __FILE__ << "\", func: \"" << __FUNCTION__ << "\" in line " << __LINE__ << " ==> "

Huffman::HuffmanNode* Huffman::HuffmanTree::add_node(const std::vector<bool> &code) {
    HuffmanNode* current = &root;
    for (bool bit : code) {
        if (bit) {
            if (!current->right)
                current->right = std::make_unique<HuffmanNode>();
            current = current->right.get();
        } else {
            if (!current->left)
                current->left = std::make_unique<HuffmanNode>();
            current = current->left.get();
        }
    }
    return current;
}

uint8_t Huffman::HuffmanTree::decode_symbol(BitReader &b_reader) {
    Huffman::HuffmanNode* current = &root;
    while (true) {
        bool bit;
        b_reader >> bit;
        if (bit) {
            if (current->left)
                current = current->right.get();
        } else {
            if (current->right)
                current = current->left.get();
        }

        if (!current->left && !current->right) {
            return current->symbol;
        }
    }
}

void Huffman::HuffmanTree::read_tree(BitReader &b_reader) {
    root.read_in_tree(b_reader);
}

void Huffman::HuffmanTree::write_tree(BitWriter &b_writer) const {
    root.write_in_tree(b_writer);
}

Huffman::HuffmanNode &Huffman::HuffmanTree::get() {
    return root;
}


void Huffman::HuffmanNode::write_in_tree(BitWriter &b_writer) const {
    if (!left && !right)
        b_writer << true << symbol;
    else
        b_writer << false;

    if (left)
        left->write_in_tree(b_writer);
    if (right)
        right->write_in_tree(b_writer);
}

void Huffman::HuffmanNode::read_in_tree(BitReader &b_reader) {
    bool bit;
    b_reader >> bit;
    if (b_reader.eof())
        return;
    if (bit) {
        b_reader >> symbol;
        return;
    }
    left = std::make_unique<HuffmanNode>();
    right = std::make_unique<HuffmanNode>();
    left->read_in_tree(b_reader);
    right->read_in_tree(b_reader);
}

#undef PLACE