#include "BitWriter.h"

BitWriter::BitWriter(std::ostream &os) : ostream(os) {}

void BitWriter::flush() {
    ostream.put(buff);
    buff = 0;
    pos = 0;
    written_bytes++;
}

BitWriter::~BitWriter() {
    if (pos > 0)
        flush();
}

BitWriter &BitWriter::operator<<(bool bit) {
    if (pos == 8)
        flush();

    buff |= bit << (7 - pos);
    pos++;
    return *this;
}

int BitWriter::get_written_bytes() {
    return written_bytes + (pos > 0);
}