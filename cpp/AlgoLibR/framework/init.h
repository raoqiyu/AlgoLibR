//
// Created by raoqiyu on 2020/9/5.
//
#pragma once

#ifndef ALGOLIBR_CPP_ALGOLIBR_FRAMEWORK_INIT_H_
#define ALGOLIBR_CPP_ALGOLIBR_FRAMEWORK_INIT_H_

#include <clocale>
#include <iostream>


namespace AlgoLibR {
inline void init_wcout() {
    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale(""));
}
} // namespace AlgoLibR

#endif //ALGOLIBR_CPP_ALGOLIBR_FRAMEWORK_INIT_H_
