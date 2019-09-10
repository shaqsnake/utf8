// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:41:29
 * @LastEditTime: 2019-09-10 11:24:04
 * @Description: An implementation of class utf8::Utf8.
 */

#include <string>
#include <utf8/Utf8.hpp>
#include <iostream>

namespace {
    /**
     * Unicode replacement character (�) which is encoded as UTF-8.
     */
    const std::vector<utf8::Utf8Unit> UTF8_ENCODED_REPLACEMENT_CHARACTER = {0xEF, 0xBF, 0xBD};

    /**
     * Unicode replacement character (�) as a unicode code point.
     */
    const utf8::UnicodeUnit UNICODED_REPLACEMENT_CHARACTER = 0xFFFD;

    /**
     * The high and low surrogate halves used by UTF-16 (U+D800 through U+DFFF)
     * and code points not encodable by UTF-16 (those after U+10FFFF) are
     * not legal Unicode values, and their UTF-8 encoding must be treated as
     * an invalid byte sequence.
     */
    const utf8::UnicodeUnit FIRST_SURROGATE = 0xD800;
    const utf8::UnicodeUnit LAST_SURROGATE = 0xDFFF;

    /**
     * The last code point in Unicode which is legal.
     */
    const utf8::UnicodeUnit LAST_LEGAL_UNICODE = 0x10FFFF;

    /**
     * @description:
     *     Calculate how many bits in a unicode code point.
     * @param[in] codePoint
     *     A code point of unicode.
     * @return:
     *     The num of bits is returned.
     */
    size_t calculateBits(utf8::UnicodeUnit codePoint) {
        size_t bits = 0;
        while (codePoint) {
            bits++;
            codePoint >>= 1;
        }

        return bits;
    }
}

namespace utf8 {
/**
 * @description:
 *     This fuction parse every ascii charater to its unicode.
 * @param[in] asciis
 *     The string is composed by ascii charaters.
 * @return:
 *     A collection of Unicodes is returned.
 */
std::vector<UnicodeUnit> asciiToUnicode(const std::string &asciis) {
    return std::vector<UnicodeUnit>(asciis.begin(), asciis.end());
}

/**
 * @description:
 *     Encode Unicode with UTF-8 format.
 * @param[in]
 *     A collection of Unicodes.
 * @return:
 *     A coolection of UTF-8 codes is returned.
 */
std::vector<Utf8Unit> Utf8::encode(const std::vector<UnicodeUnit> &unicodes) {
    std::vector<Utf8Unit> res;
    for (auto const unicode : unicodes) {
        const auto bits = calculateBits(unicode);
        if (bits <= 7) {
            res.push_back(static_cast<Utf8Unit>(unicode & 0x7F));
        } else if (bits <= 11) {
            res.push_back(static_cast<Utf8Unit>(unicode >> 6 & 0x1F) + 0xC0);
            res.push_back(static_cast<Utf8Unit>(unicode & 0x3F) + 0x80);
        } else if (bits <= 16) {
            if (unicode >= FIRST_SURROGATE && unicode <= LAST_SURROGATE) {
                res.insert(res.end(), UTF8_ENCODED_REPLACEMENT_CHARACTER.begin(), UTF8_ENCODED_REPLACEMENT_CHARACTER.end());
            } else {
                res.push_back(static_cast<Utf8Unit>(unicode >> 12 & 0x0F) + 0xE0);
                res.push_back(static_cast<Utf8Unit>(unicode >> 6 & 0x3F) + 0x80);
                res.push_back(static_cast<Utf8Unit>(unicode & 0x3F) + 0x80);
            }
        } else if (bits <= 21 && unicode <= LAST_LEGAL_UNICODE) {
            res.push_back(static_cast<Utf8Unit>(unicode >> 18 & 0x07)  + 0xF0);
            res.push_back(static_cast<Utf8Unit>(unicode >> 12 & 0x3F)  + 0x80);
            res.push_back(static_cast<Utf8Unit>(unicode >> 6 & 0x3F) + 0x80);
            res.push_back(static_cast<Utf8Unit>(unicode & 0x3F) + 0x80);
        } else {
            res.insert(res.end(), UTF8_ENCODED_REPLACEMENT_CHARACTER.begin(), UTF8_ENCODED_REPLACEMENT_CHARACTER.end());
        }
    }

    return res;
}

/**
 * @description:
 *     Decode UTF-8 encoded sequece to unicode code points.
 * @param[in] utf8codes
 *     Input sequence with UTF-8 encoding.
 * @return:
 *     A sequence of unicode code points is returned.
 */
std::vector<UnicodeUnit> Utf8::decode(const std::vector<Utf8Unit> &utf8codes) {
    std::vector<UnicodeUnit> res;
    int remainDecoding = 0;
    UnicodeUnit curUnicode = 0x00;
    // for (auto hex : utf8codes) {
    for (auto iter = utf8codes.begin(); iter != utf8codes.end(); ++iter) {
        if (remainDecoding) {
            if ((*iter & 0xC0) != 0x80) {
                res.push_back(UNICODED_REPLACEMENT_CHARACTER);
                remainDecoding = 0;
                curUnicode = 0x00;
                iter--;
                // continue;
            } else {
                curUnicode <<= 6;
                curUnicode += (*iter & 0x3F);
                remainDecoding--;
                if (remainDecoding == 0) {
                    res.push_back(curUnicode);
                    curUnicode = 0x00;
                }
            }
        } else {
            if ((*iter & 0x80) == 0x00) { // 0xxxxxxx
                res.push_back(*iter);
                remainDecoding = 0;
            } else if ((*iter & 0xE0) == 0xC0) { // 110xxxxx 10xxxxxx
                remainDecoding = 1;
                curUnicode = (*iter & 0x1F);
            } else if ((*iter & 0xF0) == 0xE0) { // 1110xxxx 10xxxxxx 10xxxxxx
                remainDecoding = 2;
                curUnicode = (*iter & 0x1F);
            } else if ((*iter & 0xF8) == 0xF0) { // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                remainDecoding = 3;
                curUnicode = (*iter & 0x0E);
            } else {
                res.push_back(UNICODED_REPLACEMENT_CHARACTER);
            }
        }
    }

    return res;
}

/**
 * @description:
 *     Decode a raw string to unicode code points.
 * @param[in] utf8codes
 *     Input raw string.
 * @return:
 *     A sequence of unicode code points is returned.
 */
std::vector<UnicodeUnit> Utf8::decode(const std::string &str) {
    return decode(std::vector<utf8::Utf8Unit>(str.begin(), str.end()));
}

} // namespace utf8
