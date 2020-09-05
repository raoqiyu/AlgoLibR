/*
Author: raoqiyu@gmail.com
Date: 2020-02-17 17:06:06
FilePath: /AlgoLibR/cpp/AlgoLibR/framework/string.h
Description: 
 */

#pragma once

#ifndef FRAMEWORK_STRING_H
#define FRAMEWORK_STRING_H

#include <string>
#include <vector>
#include <regex>

namespace AlgoLibR{
namespace framework{
namespace string{

char * Unicode2MBCS(char * buff, const wchar_t * str);

wchar_t* MBCS2Unicode(wchar_t * buff, const char * str);

std::string wstr2str(std::wstring wstr);

std::wstring str2wstr(std::string str);

void split(const std::wstring& str, std::vector<std::wstring>& sub_strs, const std::wstring& delimiters);

const static std::wstring g_re_pattern_str = L"([\u4E00-\u9FD5a-zA-Z0-9+#&._%-]+)";

bool regex_wsplit(const std::wstring& str, std::vector<std::wstring>& sub_strs, 
                    std::vector<unsigned int>& sub_strs_kind, const std::wstring& pattern_str=g_re_pattern_str);


bool regex_wsplit(const wchar_t*  str, std::vector<std::wstring>& sub_strs,
        std::vector<unsigned int>& sub_strs_kind, const std::wstring& pattern_str=g_re_pattern_str );

} // namespace
}
}

#endif