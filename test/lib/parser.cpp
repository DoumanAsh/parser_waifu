#include <string>

#include "parser.hpp"
using namespace parser;

#include "gtest/gtest.h"
using namespace ::testing;

TEST(LibParser, ShouldMecabParse) {
    Mecab mecab;
    const std::string str(u8"かわいい");

    mecab.parse(str);
}
