#pragma once

#include <iostream>

class BitWriter {
public:
    BitWriter(std::ostream &os);

    ~BitWriter();

    BitWriter &operator<<(bool bit);

    template<typename T>
    BitWriter &operator<<(T &symbol) {
        int byte_size = sizeof(T);
        const uint8_t *byte = reinterpret_cast<const uint8_t *>(&symbol) + (byte_size - 1);

        for (int i = 0; i < byte_size; i++, byte--) {
            for (int b = 7; b >= 0; b--) {
                *this << static_cast<bool>((*byte >> b) & 1);
            }
        }
        return *this;
    }


  template<typename T>
  BitWriter &operator<<(T &&symbol) { return *this << symbol; }

    int get_written_bytes();

private:
    int pos = 0;
    int written_bytes = 0;
    uint8_t buff = 0;
    std::ostream &ostream;

    void flush();
};//end class BitWriter