#include <string>

#include "utils.hpp"
using namespace utils;

#include "gtest/gtest.h"
using namespace ::testing;

TEST(LibUtils, ShouldFindJpChars) {
    const std::wstring str(L"かわいい");

    ASSERT_TRUE(is_jp(str));
}

TEST(LibUtils, ShouldNotFindJpChars) {
    const std::wstring str(L"Cute");

    ASSERT_FALSE(is_jp(str));
}

TEST(LibUtils, ShouldFindJpCharsInPartialStr) {
    const std::wstring str(L"かわいい＝Cute");

    ASSERT_TRUE(is_jp(str));
}
