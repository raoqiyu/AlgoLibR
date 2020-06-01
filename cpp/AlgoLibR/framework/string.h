/*
Author: raoqiyu@gmail.com
Date: 2020-02-17 17:06:06
FilePath: /AlgoLibR/cpp/AlgoLibR/framework/string.h
Description: 
 */

#ifndef FRAMEWORK_STRING_H
#define FRAMEWORK_STRING_H

#include <string>
#include <vector>
#include <regex>

namespace AlgoLibR{
namespace framework{
namespace string{

char * Unicode2MBCS(char * buff, const wchar_t * str){ 
    wchar_t * wp = (wchar_t *)str;

    char * p = buff, *tmp;

    while (*wp) {
         tmp = (char *)wp;
         if (*wp & 0xFF00) {
             *p = *tmp;
             p++; tmp++;
             *p = *tmp;
             p++;
        }else {
         *p = *tmp;
         p++;
        }
        
        wp++;
    }
    *p = 0x00;
    return buff;
 
}

wchar_t* MBCS2Unicode(wchar_t * buff, const char * str){
    wchar_t * wp = buff;
    char * p = (char *)str;

    while (*p){
        if (*p & 0x80){
            *wp = *(wchar_t *)p;
            p++;
        }else {
            *wp = (wchar_t)*p;
        }
        wp++;
        p++;
    }
    *wp = 0x0000; 
    return buff;
}

std::string wstr2str(std::wstring wstr){

    size_t len = wstr.size();

    char * b = (char *)malloc((2 * len + 1) * sizeof(char));
    Unicode2MBCS(b, wstr.c_str());
    std::string r(b);
 
    free(b);

    return r;
}

std::wstring str2wstr(std::string str){
    size_t len = str.size(); 
    wchar_t * b = (wchar_t *)malloc((len + 1) * sizeof(wchar_t));
    MBCS2Unicode(b, str.c_str());
    std::wstring r(b); 
    free(b); 
    return r;
}

void split(const std::wstring& str, std::vector<std::wstring>& sub_strs, const std::wstring& delimiters){
	std::wstring::size_type last_pos = str.find_first_not_of(delimiters, 0);
	std::wstring::size_type pos = str.find_first_of(delimiters, last_pos+1);
	while(std::wstring::npos != pos || std::wstring::npos != last_pos){
		sub_strs.push_back(str.substr(last_pos, pos-last_pos));
		last_pos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, last_pos);
	}
}

const std::wstring g_re_pattern_str = L"([\u4E00-\u9FD5a-zA-Z0-9+#&._%-]+)";

void regex_wsplit(const std::wstring& str, std::vector<std::wstring>& sub_strs){
    std::wstring s(str);
    std::wregex pattern(g_re_pattern_str);
    std::wsmatch result;
    std::wstring text;
    while(true){
        if(!std::regex_search(s, result, pattern)){
            if(s.size() > 0)
                sub_strs.push_back(s);
            break;
        }
        text = result.prefix();
        if(text.size() > 0)
            sub_strs.push_back(text);
        for(auto x = result.begin()+1; x != result.end(); x++){
            text = x->str();
            if(text.size() > 0)
                sub_strs.push_back(text);
        }
        s = result.suffix().str();
    }
}

} // namespace
}
}

#endif