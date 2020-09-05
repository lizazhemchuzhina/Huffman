#include "BitReader.h"

BitReader::BitReader(std::istream &is) : istream(is) {}


BitReader &BitReader::operator>>(bool &bit) {
    if (pos == 0)
        getNext();

    if (end_of_file)
        return *this;

    bit = (buff >> (pos - 1)) & 1;
    pos--;
    return *this;
}

bool BitReader::eof() {
    return end_of_file;
}

int BitReader::get_read_bytes() {
    return read_bytes;
}

void BitReader::getNext() {
    if (end_of_file)
        return;
    buff = istream.get();
    pos = 8;
    read_bytes++;

    if (istream.eof())
        end_of_file = true;
}