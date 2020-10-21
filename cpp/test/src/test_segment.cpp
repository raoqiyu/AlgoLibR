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
#include <gtest/gtest.h>

#include "AlgoLibR/ai/nlp/seg/ahocorasick_segment.h"


using namespace AlgoLibR::ai::nlp::seg;

TEST(test_ac_segment, english){
    std::wcout << "\nTest AC Segmentation" << std::endl << std::flush;

    AhoCorasickSegment ac_segment;
    ac_segment.SetSegAll(false);

    ac_segment.Build("./data/NLP/Dictionary/test_dict.txt", L"    ");

    std::wstring sentence(L"Ilovechinachinaloveme");

    std::vector<std::wstring> segmented = ac_segment.SegSentence(sentence.c_str());
    
    for(auto & i : segmented){
        std::wcout << i << " " ;
    }
    std::wcout << std::endl;
}

TEST(test_ac_segment, chinese){
    
    std::wcout << "\nTest AC Segmentation ZH" << std::endl;

    AhoCorasickSegment ac_segment;
    ac_segment.SetSegAll(false);

    ac_segment.Build("./data/NLP/Dictionary/jieba_dict.txt.big", L" ");

    std::wstring sentence(L"Hello World!《三国演义》描写H1N1了从东汉末3.1415926年到西晋H20初年之间近百年的历史风云，以描写战争为主，诉说了东汉末年的群雄割据混战和魏、蜀、吴三国之间的政治和军事斗争，最终司马炎一统三国，建立晋朝的故事。反映了三国时代各类社会斗争与矛盾的转化，并概括了这一时代的历史巨变，塑造了一群叱咤风云的三国英雄人物。");

    std::vector<std::wstring> segmented = ac_segment.Segment(sentence.c_str());
    
    for(auto & i : segmented){
        std::wcout << i << " " ;
    }
    std::wcout << std::endl;
}