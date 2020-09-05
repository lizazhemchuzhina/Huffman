#pragma once

#include <iostream>

class BitReader {
public:
    BitReader(std::istream &is);

    BitReader &operator>>(bool &bit);

    template<typename T>
    BitReader &operator>>(T &symbol) {
        int byte_size = sizeof(T);
        uint8_t *byte = reinterpret_cast<uint8_t*>(&symbol) + (byte_size - 1);

        bool bit = false;
        for (int i = 0; i < byte_size; i++, byte--) {
            *byte = 0;
            for (int b = 7; b >= 0; b--) {
                *this >> bit;
                *byte |= bit << b;
            }
        }
        return *this;
    }

    bool eof();

    int get_read_bytes();

private:
    int pos = 0;
    uint8_t buff = 0;
    bool end_of_file = false;
    std::istream &istream;
    int read_bytes = 0;

    void getNext();
};// end class BitReader