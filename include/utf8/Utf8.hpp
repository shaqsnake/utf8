// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:41:18
 * @LastEditTime: 2019-08-20 14:53:22
 * @Description: A declaration of class utf8::Utf8.
 */

#ifndef UTF8_UTF8_HPP
#define UTF8_UTF8_HPP

namespace utf8 {

class Utf8 {
public:
    Utf8() = default;
    ~Utf8() = default;
    Utf8(const Utf8 &) = delete;
    Utf8(Utf8 &&) = delete;
    Utf8 &operator=(const Utf8 &) = delete;
    Utf8 &operator=(Utf8 &&) = delete;
    
public:
    int foo();
};


} // namespace utf8

#endif // UTF8_UTF8_HPP
