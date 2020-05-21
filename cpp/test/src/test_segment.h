/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-17 11:25:48
FilePath: /AlgoLibR/cpp/test/src/test_segment.h
 * @Description: 
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "AlgoLibR/ai/nlp/seg/ahocorasick_segment.h"

using namespace AlgoLibR::ai::nlp::seg;

void test_ac_segment(){
    std::wcout << "\nTest AC Segmentation" << std::endl << std::flush;

    AhoCorasickSegment ac_segment;
    ac_segment.SetSegAll(false);

    ac_segment.Build("../../data/NLP/Dictionary/test_dict.txt");

    std::wstring sentence(L"Ilovechinachinaloveme");

    std::vector<std::wstring> segmented = ac_segment.SegSentence(sentence.c_str());
    
    for(auto i = 0; i < segmented.size(); i++){
        std::wcout << segmented[i] << " " ;
    }
    std::wcout << std::endl;
}

void test_ac_segment_zh(){
    
    std::wcout << "\nTest AC Segmentation ZH" << std::endl;

    AhoCorasickSegment ac_segment;
    ac_segment.SetSegAll(false);

    ac_segment.Build("../../data/NLP/Dictionary/test_dict_zh.txt");

    std::wstring sentence(L"我去参观北京天安门");

    std::vector<std::wstring> segmented = ac_segment.SegSentence(sentence.c_str());
    
    for(auto i = 0; i < segmented.size(); i++){
        std::wcout << segmented[i] << "," ;
    }
    std::wcout << std::endl;
}

void test_segment(){
    test_ac_segment();
    test_ac_segment_zh();
}