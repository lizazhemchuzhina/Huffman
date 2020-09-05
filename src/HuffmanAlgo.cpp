#include "HuffmanAlgo.h"
#define PLACE() "in file: \"" << __FILE__ << "\", func: \"" << __FUNCTION__ << "\" in line " << __LINE__ << " ==> "

void HuffmanAlgo::set_frequency(std::istream &is) {
    char c;
    for (symbols_count = 0; is.get(c); symbols_count++) {
        freq_sym[static_cast<uint8_t>(c)]++;
    }
}

void HuffmanAlgo::fill_codes_heap(std::priority_queue<frequency> &codes_heap) {
    for (size_t i = 0; i < freq_sym.size(); i++) {
        if (freq_sym[i]) {
            codes_heap.push({freq_sym[i], static_cast<uint8_t>(i) });
        }
    }
}

int HuffmanAlgo::calculate_codes_by_heap(std::priority_queue<frequency> &codes_heap, int index) {
    if (codes_heap.size() <= 1) {
        if (codes_heap.empty())
            return 256;
        frequency first_min = codes_heap.top();
        codes[first_min.symbol].push_back(false);
        codes_tree.get().symbol = first_min.symbol;
        return 256;
    }

    frequency first_min = codes_heap.top();
    codes_heap.pop();
    frequency second_min = codes_heap.top();
    codes_heap.pop();

    frequency combined = {first_min.freq + second_min.freq, first_min.symbol};
    codes_heap.push(combined);

    int result = calculate_codes_by_heap(codes_heap, first_min.symbol);

    codes[first_min.symbol] = codes[result];
    codes[second_min.symbol] = codes[result];

    codes[first_min.symbol].push_back(false);
    codes[second_min.symbol].push_back(true);

    codes_tree.add_node(codes[first_min.symbol])->symbol = first_min.symbol;
    codes_tree.add_node(codes[second_min.symbol])->symbol = second_min.symbol;

    return index;
}

void HuffmanAlgo::build_codes(std::istream &is) {
    set_frequency(is);
    if (symbols_count == 0)
        return;

    std::priority_queue<frequency> codes_heap;
    fill_codes_heap(codes_heap);
    calculate_codes_by_heap(codes_heap);
}

std::vector<std::vector<bool>> &HuffmanAlgo::get_codes() {
    return codes;
}

HuffmanTree &HuffmanAlgo::get_codes_tree() {
    return codes_tree;
}

uint32_t &HuffmanAlgo::get_symbols_count() {
    return symbols_count;
}

std::vector<int> &HuffmanAlgo::get_freq() {
    return freq_sym;
}
