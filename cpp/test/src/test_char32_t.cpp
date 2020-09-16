//
// Created by raoqiyu on 2020/9/16.
//


#include <iostream>
#include <gtest/gtest.h>


TEST(test_char32,basic){
    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale("zh_CN.utf-8"));

    char32_t words[] = U"测试";

    std::cout << words[0] << ',' << words[1] << std::endl;
    std::wcout << (wchar_t *)words  << std::endl;
    ASSERT_EQ(words[0], 27979);
    ASSERT_EQ(words[1], 35797);
}