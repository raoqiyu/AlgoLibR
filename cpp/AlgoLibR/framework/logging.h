//
// Created by raoqiyu on 2020/8/31.
//
#pragma once

#ifndef ALGOLIBR_CPP_ALGOLIBR_FRAMEWORK_LOGGING_H_
#define ALGOLIBR_CPP_ALGOLIBR_FRAMEWORK_LOGGING_H_

#include <cstdarg>
#include <iostream>

#ifndef ALGOLIBR_CPP_ALGOLIBR_FRAMEWORK_INIT_H_
#include "AlgoLibR/framework/init.h"
#endif

namespace AlgoLibR {

#ifndef LOGGING_INFO
#define LOGGING_INFO(fmt, ...) logging(__FILENAME__, __FUNCTION__, __LINE__, L"  INFO ", fmt, ##__VA_ARGS__);
#endif

#ifndef LOGGING_DEBUG
#define LOGGING_DEBUG(fmt, ...) logging(__FILENAME__, __FUNCTION__, __LINE__, L" DEBUG ", fmt, ##__VA_ARGS__);
#endif

#ifndef LOGGING_WARNING
#define LOGGING_WARNING(fmt, ...) logging(__FILENAME__, __FUNCTION__, __LINE__, L"WARNING", fmt, ##__VA_ARGS__);
#endif

#ifndef LOGGING_ERROR
#define LOGGING_ERROR(fmt, ...) logging(__FILENAME__, __FUNCTION__, __LINE__, L" ERROR ", fmt, ##__VA_ARGS__);
#endif

inline void logging(const char *file, const char *func, int line, wchar_t *lvl, wchar_t *fmt, ...) {

#ifndef INIT_WCOUT
#define INIT_WCOUT
    init_wcout();
#endif

    va_list argptr;
    va_start(argptr, fmt);
    wchar_t buffer[1024] = {0};
    vswprintf(buffer, 1024, fmt, argptr);
    va_end(argptr);

    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));

    std::wcout << "[" <<tmp << "][" << lvl << "][" << file << ":L" << line << "][" << func << "]:" << buffer << std::endl;
}

//#ifndef INIT_WCOUT
//int _ = AlgoLibR::init_wcout();
//#endif

}// namespace AlgoLibR

#endif //ALGOLIBR_CPP_ALGOLIBR_FRAMEWORK_LOGGING_H_

