// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:41:29
 * @LastEditTime: 2019-08-21 16:31:24
 * @Description: An implementation of class utf8::Utf8.
 */

#include <string>
#include <utf8/Utf8.hpp>

namespace {
    size_t calulateBits(utf8::UnicodeUnit codePoint) {
        size_t bits = 0;
        while (codePoint) {
            bits++;
            codePoint = codePoint >> 1;
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
        const auto bits = calulateBits(unicode);
        if (bits <= 7) {
            res.push_back(static_cast<Utf8Unit>(unicode & 0x7F));
        } else if (bits <= 11) {
            res.push_back(static_cast<Utf8Unit>(unicode >> 6 & 0x1F) + 0xC0);
            res.push_back(static_cast<Utf8Unit>(unicode & 0x3F) + 0x80);
        } else if (bits <= 16) {
            res.push_back(static_cast<Utf8Unit>(unicode >> 12 & 0x0F) + 0xE0);
            res.push_back(static_cast<Utf8Unit>(unicode >> 6 & 0x3F) + 0x80);
            res.push_back(static_cast<Utf8Unit>(unicode & 0x3F) + 0x80);
        } else {
            res.push_back(static_cast<Utf8Unit>(unicode >> 18 & 0x07)  + 0xF0);
            res.push_back(static_cast<Utf8Unit>(unicode >> 12 & 0x3F)  + 0x80);
            res.push_back(static_cast<Utf8Unit>(unicode >> 6 & 0x3F) + 0x80);
            res.push_back(static_cast<Utf8Unit>(unicode & 0x3F) + 0x80);
        }
    }

    return res;
}

} // namespace utf8
