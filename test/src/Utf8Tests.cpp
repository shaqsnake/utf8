// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-08-20 14:48:52
 * @LastEditTime: 2019-08-20 14:55:51
 * @Description: Unittests of class utf8::Utf8.
 */

#include <gtest/gtest.h>
#include <utf8/Utf8.hpp>

TEST(Utf8Tests, Placeholder) {
    utf8::Utf8 utf8;
    ASSERT_EQ(42, utf8.foo());
}
