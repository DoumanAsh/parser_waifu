#include "parser/parser.hpp"
#include "parser/internal.hpp"

#include "gtest/gtest.h"
using namespace ::testing;

TEST(LibParser, MecabParseWorks) {
    parser::Mecab mecab;
    //Uses char codes for "tekito" to avoid damn VC++ codepage trouble
    const std::string str(u8"\u624B\u5143");

    mecab.parse(str);
}

TEST(LibParser, should_escape_html) {
    const auto escaped = parser::internal::escape_html(">>< &' test \"");

    ASSERT_STREQ(escaped.c_str(), "&gt;&gt;&lt; &amp;&apos; test &quot;");
}
