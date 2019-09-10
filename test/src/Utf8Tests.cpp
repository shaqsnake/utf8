// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:48:52
 * @LastEditTime: 2019-09-10 11:33:14
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
    const auto actual = utf8.encode({0x0041, 0x2262, 0x0391, 0x002E}); // A≢Α.
    ASSERT_EQ(expected, actual);
}

TEST(Utf8Tests, EncodeWithInvaildRange) {
    const std::vector<utf8::Utf8Unit> replacementChar{0xEF, 0xBF, 0xBD};
    utf8::Utf8 utf8;
    ASSERT_EQ(replacementChar, utf8.encode({0x110000}));
    ASSERT_EQ(replacementChar, utf8.encode({0x120000}));
    ASSERT_EQ(replacementChar, utf8.encode({0xD800}));
    ASSERT_EQ(replacementChar, utf8.encode({0xD801}));
    ASSERT_EQ(replacementChar, utf8.encode({0xDFFE}));
    ASSERT_EQ(replacementChar, utf8.encode({0xDFFF}));
}

TEST(Utf8Tests, DecodeValidSequences) {
    struct TestCase {
        std::vector<utf8::Utf8Unit> utf8Seq;
        std::vector<utf8::UnicodeUnit> expected;
    };
    std::vector<TestCase> testCases {
        {{0x2E}, {0x002E}},
        {{0x55, 0x74, 0x66, 0x2D, 0x38}, {0x55, 0x74, 0x66, 0x2D, 0x38}},
        {{0xF0, 0xA3, 0x8E, 0xB4}, {0x233B4}},
        {{0xE6, 0x97, 0xA5, 0xE6, 0x9C, 0xAC, 0xE8, 0xAA, 0x9E}, {0x65E5, 0x672C, 0x8A9E}},
        {{0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x91, 0x2E}, {0x0041, 0x2262, 0x0391, 0x002E}},
    };

    utf8::Utf8 utf8;
    size_t idx = 0;
    for (const auto testCase : testCases) {
        auto actual = utf8.decode(testCase.utf8Seq);
        ASSERT_EQ(testCase.expected, actual)
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(Utf8Tests, DecodeValidString) {
    struct TestCase {
        std::string rawStr;
        std::vector<utf8::UnicodeUnit> expected;
    };
    std::vector<TestCase> testCases {
        {"Utf-8", {0x55, 0x74, 0x66, 0x2D, 0x38}},
        {"𣎴", {0x233B4}},
        {"日本語", {0x65E5, 0x672C, 0x8A9E}},
        {"A≢Α.", {0x0041, 0x2262, 0x0391, 0x002E}},
        {"€", {0x20AC} },
    };

    utf8::Utf8 utf8;
    size_t idx = 0;
    for (const auto testCase : testCases) {
        auto actual = utf8.decode(testCase.rawStr);
        ASSERT_EQ(testCase.expected, actual)
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}

TEST(UtfTests, DecodeInvalidSequence) {
    struct TestCase {
        std::vector<utf8::Utf8Unit> inputSequence;
        std::vector<utf8::UnicodeUnit> expected;
    };
    std::vector<TestCase> testCases {
        {{0x41, 0xE2, 0x89, 0xA2, 0x91, 0x2E}, {0x0041, 0x2262, 0xFFFD, 0x002E}},
        {{0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x2E}, {0x0041, 0x2262, 0xFFFD, 0x002E}},
        {{0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x2E, 0x2E}, {0x0041, 0x2262, 0xFFFD, 0x002E, 0x002E}},
        {{0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x2E, 0xCE, 0x2E}, {0x0041, 0x2262, 0xFFFD, 0x002E, 0xFFFD, 0x002E}},
    };

    utf8::Utf8 utf8;
    size_t idx = 0;
    for (const auto testCase : testCases) {
        auto actual = utf8.decode(testCase.inputSequence);
        ASSERT_EQ(testCase.expected, actual)
            << ">>> Test is failed at " << idx << ". <<<";
        ++idx;
    }
}
