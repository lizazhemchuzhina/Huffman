#include <fstream>
#include <vector>
#include "BitWriter.h"
#include "BitReader.h"
#include "HuffmanAlgo.h"

class HuffmanArchiver {
public:
    HuffmanArchiver(std::ifstream &is, std::ofstream &os) : ifs(is), ofs(os) {}

    void encode(bool info = false);

    void decode(bool info = false);

private:

    std::ifstream &ifs;
    std::ofstream &ofs;
    void reset_input_stream() const;

    void write_result(BitWriter &b_writer, const std::vector<std::vector<bool>> &codes) const;

    void decode_file_with_tree(HuffmanAlgo &alg, BitReader &b_reader) const;
};