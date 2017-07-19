#include <string>

#include "utils.hpp"
using namespace utils;

#include "gtest/gtest.h"
using namespace ::testing;

TEST(LibUtils, ShouldFindJpChars) {
    const std::wstring wstr(L"かわいい");
    ASSERT_TRUE(is_jp(wstr));

    const std::string str(u8"かわいい");
    ASSERT_TRUE(is_jp(str));
}

TEST(LibUtils, ShouldNotFindJpChars) {
    const std::wstring wstr(L"Cute");
    ASSERT_FALSE(is_jp(wstr));

    const std::string str(u8"Cute");
    ASSERT_FALSE(is_jp(str));
}

TEST(LibUtils, ShouldFindJpCharsInPartialStr) {
    const std::wstring wstr(L"かわいい＝Cute");
    ASSERT_TRUE(is_jp(wstr));

    const std::string str(u8"かわいい＝Cute");
    ASSERT_TRUE(is_jp(str));
}
