//
// Created by raoqiyu on 2020/8/31.
//

#include <gtest/gtest.h>
//#include <locale.h>

#include "AlgoLibR/framework/logging.h"


TEST(test_logging, basic){
    std::wstring test = L"测试";
    AlgoLibR::LOGGING_INFO(L"打印 %d", 2);
    AlgoLibR::LOGGING_INFO(L"%ls, %d", test.c_str(), 2);
    AlgoLibR::LOGGING_INFO(L"%ls,%d", L"测试2", 2);
    AlgoLibR::LOGGING_DEBUG(L"%s,%d", "hi", 2);
    AlgoLibR::LOGGING_WARNING(L"%s,%d", "hi", 2);
    AlgoLibR::LOGGING_ERROR(L"%s,%d", "hi", 2);
}
