#include <string>

#include "parser.hpp"
using namespace parser;

#include "gtest/gtest.h"
using namespace ::testing;

TEST(LibParser, ShouldMecabParse) {
    Mecab mecab;
    //TODO: On windows it should be L"" due to encoding of char*
    const std::string str("かわいい");

    const auto result = mecab.parse(str);
    std::cout  << result << std::endl;
}
