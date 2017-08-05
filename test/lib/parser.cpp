#include "parser/parser.hpp"
using namespace parser;

#include "gtest/gtest.h"
using namespace ::testing;

TEST(LibParser, MecabParseWorks) {
    Mecab mecab;
    //Uses char codes for "tekito" to avoid damn VC++ codepage trouble
    const std::string str(u8"\u624B\u5143");

    mecab.parse(str);
}
