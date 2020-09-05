
cmake_minimum_required(VERSION 3.10)
project(Huffman_archiver)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(Huffman_archiver src/main.cpp src/Huffman.cpp include/Huffman.h src/HuffmanArchiver.cpp include/HuffmanArchiver.h src/CLI.cpp include/CLI.h src/HuffmanAlgo.cpp include/HuffmanAlgo.h src/BitReader.cpp include/BitReader.h src/BitWriter.cpp include/BitWriter.h)
add_executable(Huffman_archiver_test src/Huffman.cpp include/Huffman.h src/HuffmanArchiver.cpp include/HuffmanArchiver.h src/CLI.cpp include/CLI.h src/HuffmanAlgo.cpp include/HuffmanAlgo.h
        src/BitReader.cpp include/BitReader.h src/BitWriter.cpp include/BitWriter.h test/TestMain.cpp test/TestBinStream.cpp test/TestEndToEnd.cpp test/TestPartsAlgo.cpp)
