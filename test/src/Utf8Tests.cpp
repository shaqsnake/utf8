// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:48:52
 * @LastEditTime: 2019-08-26 09:42:36
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
    const auto actual = utf8.encode({0x233B4}); // 不
    ASSERT_EQ(expected, actual);
}

TEST(Utf8Tests, EncodeKorean) {
    const std::vector<utf8::Utf8Unit> expected{0xED, 0x95, 0x9C, 0xEA, 0xB5, 0xAD, 0xEC, 0x96, 0xB4};
    utf8::Utf8 utf8;
    const auto actual = utf8.encode({0xD55C, 0xAD6D, 0xC5B4}); // 한국어
    ASSERT_EQ(expected, actual);
}

TEST(Utf8Tests, EncodeJapanese) {
    const std::vector<utf8::Utf8Unit> expected{0xE6, 0x97, 0xA5, 0xE6, 0x9C, 0xAC, 0xE8, 0xAA, 0x9E};
    utf8::Utf8 utf8;
    const auto actual = utf8.encode({0x65E5, 0x672C, 0x8A9E}); // 日本語
    ASSERT_EQ(expected, actual);
}

TEST(Utf8Tests, EncodeSymbols) {
    const std::vector<utf8::Utf8Unit> expected{0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x91, 0x2E};
    utf8::Utf8 utf8;
    const auto actual = utf8.encode({0x0041, 0x2262, 0x0391, 0x002E}); // A≢ Α.
    ASSERT_EQ(expected, actual);
}
