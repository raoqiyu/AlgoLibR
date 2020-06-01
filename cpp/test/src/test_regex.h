/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-06-01 16:09:48
FilePath: /AlgoLibR/cpp/test/src/test_regex.h
 * @Description: 
 */ 

#include <iostream>
#include <vector>
#include <string>
#include "AlgoLibR/framework/string.h"


using namespace AlgoLibR::framework::string;

void test_regex_split(){
    std::wstring s = L"为检测当前语言环境是否使用UTF-8 编码。首先必须调用 setlocale(LC_CTYPE, “”) 函数，依据环境变量设置语言环境。nl_langinfo(CODESET) 函数也是由 locale charmap 命令调用，从而查找当前语言环境指定的编码名称。";
    std::vector<std::wstring> sub_strs;

    regex_wsplit(s, sub_strs);

    for(auto x:sub_strs){
    	std::wcout << x << std::endl;
    }
}

