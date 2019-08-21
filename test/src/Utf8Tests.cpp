// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:48:52
 * @LastEditTime: 2019-08-21 16:32:10
 * @Description: Unittests of class utf8::Utf8.
 */

#include <gtest/gtest.h>
#include <utf8/Utf8.hpp>

TEST(Utf8Tests, ParseAsciiToUnicode) {
    const std::vector<utf8::UnicodeUnit> expected = {0x55, 0x74, 0x66, 0x2D, 0x38};
    const auto actual = utf8::asciiToUnicode("Utf-8");
    ASSERT_EQ(expected, actual);
}

TEST(Utf8Tests, EncodeAscii) {
    const std::vector<utf8::Utf8Unit> expected = {0x55, 0x74, 0x66, 0x2D, 0x38};
    utf8::Utf8 utf8;
    const auto actual = utf8.encode(utf8::asciiToUnicode("Utf-8"));
    ASSERT_EQ(expected, actual);
}

TEST(Utf8Tests, EncodeChinese) {
    const std::vector<utf8::Utf8Unit> expected{0xF0, 0xA3, 0x8E, 0xB4};
    utf8::Utf8 utf8;
    const auto actual = utf8.encode({0x233B4});
    ASSERT_EQ(expected, actual);
}
