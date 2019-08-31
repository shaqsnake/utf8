// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:41:18
 * @LastEditTime: 2019-08-31 14:58:01
 * @Description: A declaration of class utf8::Utf8.
 */

#ifndef UTF8_UTF8_HPP
#define UTF8_UTF8_HPP

#include <cstdint>
#include <vector>

namespace utf8 {

typedef uint32_t UnicodeUnit;
typedef uint8_t Utf8Unit;

std::vector<UnicodeUnit> asciiToUnicode(const std::string &asciis);

class Utf8 {
public:
    Utf8() = default;
    ~Utf8() = default;
    Utf8(const Utf8 &) = delete;
    Utf8(Utf8 &&) = delete;
    Utf8 &operator=(const Utf8 &) = delete;
    Utf8 &operator=(Utf8 &&) = delete;

public:
    std::vector<Utf8Unit> encode(const std::vector<UnicodeUnit>& unicodes);
    std::vector<UnicodeUnit> decode(const std::vector<Utf8Unit>& utf8codes);
    std::vector<UnicodeUnit> decode(const std::string &squence);
};


} // namespace utf8

#endif // UTF8_UTF8_HPP
