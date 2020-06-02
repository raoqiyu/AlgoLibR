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
    std::wstring s = L"Hello World!《三国演义》描H1N1写了从东汉末B2B年到西晋ofo初年之间近百年的历史风云，以描写战争为主，诉说了东汉末年的群雄割据混战32和魏、蜀、吴三国之间的LSTM政治和军事斗争，最终IT司马炎一统三国，建立BERT晋朝的故事。反映了三国时代各类社会斗争与矛盾的转化，并概括了这一时代的历史巨变，塑造了一群叱咤风云的三国英雄人物。";
    std::vector<std::wstring> sub_strs;
    std::vector<unsigned int> sub_strs_kind;

    std::wstring eng_num_patten(L"([a-zA-Z0-9]+)");

    regex_wsplit(s, sub_strs, sub_strs_kind, eng_num_patten);

    for(auto x:sub_strs){
    	std::wcout << x << std::endl;
    }
}

