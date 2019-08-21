// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:41:29
 * @LastEditTime: 2019-08-21 14:30:27
 * @Description: An implementation of class utf8::Utf8.
 */

#include <string>
#include <utf8/Utf8.hpp>

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
        res.push_back(unicode);
    }

    return res;
}

} // namespace utf8
