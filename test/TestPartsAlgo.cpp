#include "doctest.h"
#include "Huffman.h"
#include "HuffmanAlgo.h"
#include "HuffmanArchiver.h"

TEST_CASE ("empty HuffmanNode") {
    HuffmanNode n;
            CHECK_EQ(n.left, nullptr);
            CHECK_EQ(n.right, nullptr);
}


TEST_CASE ("Huffman_algo_test for empty heap") {
    HuffmanAlgo alg;
    std::priority_queue<frequency> codes_heap;
    alg.fill_codes_heap(codes_heap);
            CHECK(codes_heap.empty());
}

TEST_CASE ("Huffman_algo test for empty codes") {
    HuffmanAlgo alg;
    std::priority_queue<frequency> codes_heap;
    int res = alg.calculate_codes_by_heap(codes_heap);
            CHECK(codes_heap.empty());
            CHECK_EQ(alg.get_codes_tree().get().left, nullptr);
            CHECK_EQ(alg.get_codes_tree().get().right, nullptr);
            CHECK_EQ(res, 256);
}

TEST_CASE ("Huffman_algo test for codes_heap") {
    std::priority_queue<frequency> codes_heap;
    HuffmanAlgo alg;
    std::string test = "aaaaaaabbbbbccc";
    std::ofstream ofs("tmp.test");
    ofs<<test;
    ofs.close();
    std::ifstream ifs("tmp.test");
    alg.set_frequency(ifs);
    alg.fill_codes_heap(codes_heap);

            CHECK_EQ(codes_heap.size(), 3);
            CHECK_EQ(codes_heap.top().symbol, 'c');
            CHECK_EQ(codes_heap.top().freq, 3);
}

TEST_CASE ("Huffman_algo test for one letter code_tree") {
    std::priority_queue<frequency> code_heap;
    HuffmanAlgo alg;
    code_heap.push({4, ';'});
    int res = alg.calculate_codes_by_heap(code_heap);
            CHECK_EQ(res, 256);
            CHECK_EQ(alg.get_codes_tree().get().left, nullptr);
            CHECK_EQ(alg.get_codes_tree().get().right, nullptr);
            CHECK_EQ(alg.get_codes_tree().get().symbol, ';');
}

TEST_CASE ("Huffman_algo test for one letter code_heap") {
    std::priority_queue<frequency> code_heap;
    HuffmanAlgo alg;
    std::string test = ";;;;";
    std::ofstream ofs("tmp.test");
    ofs<<test;
    ofs.close();
    std::ifstream ifs("tmp.test");
    alg.set_frequency(ifs);
    alg.fill_codes_heap(code_heap);
            CHECK_EQ(code_heap.size(), 1);
            CHECK_EQ(code_heap.top().symbol, ';');
            CHECK_EQ(code_heap.top().freq, 4);
}