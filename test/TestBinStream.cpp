#include "doctest.h"
#include "BitReader.h"
#include "BitWriter.h"
#include <fstream>

TEST_CASE ("Binstream test write and read") {
    std::ofstream ofs("tmp.test");
    BitWriter b_writer(ofs);

    b_writer << true << false << false << true << false << true << true << true << true;
    b_writer << static_cast<char>(0);
    b_writer << static_cast<int32_t >(999999);
    ofs.close();

    std::ifstream ifs("tmp.test");
    char a;
    ifs.get(a);

            CHECK_EQ(static_cast<uint8_t>(a), 151);
    BitReader b_reader(ifs);
    bool bit;
    b_reader >> bit;
            CHECK_EQ(bit, true);

    b_reader >> a;

            CHECK_EQ(a, false);

    bool b[8];
    b_reader >> b[0] >> b[1] >> b[2] >> b[3] >> b[4] >> b[5] >> b[6] >> b[7];

            CHECK(!(b[0] || b[1] || b[2] || b[3] || b[4] || b[5] || b[6] || b[7]));

    b_reader >> a;

            CHECK_EQ(a, 15);
}
