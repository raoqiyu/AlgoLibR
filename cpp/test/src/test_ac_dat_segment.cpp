//
// Created by raoqiyu on 2020/9/16.
//


#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "AlgoLibR/ai/nlp/seg/ahocorasick_double_array_trie_segment.h"

using AlgoLibR::ai::nlp::seg::ac_dat_segment::AhoCorasickDoubleArrayTrieSegment;

TEST(test_ac_dat_segment, english){
    std::wcout << "\nTest AC Segmentation" << std::endl << std::flush;

    AhoCorasickDoubleArrayTrieSegment ac_segment;
    ac_segment.SetSegAll(true);

    ac_segment.Build("./data/NLP/Dictionary/test_dict.txt", L" ");

    std::wstring sentence(L"Ilovechinachinaloveme");

    std::vector<std::wstring> segmented = ac_segment.SegSentence(sentence);

    for(auto & i : segmented){
        std::wcout << i << " " ;
    }
    std::wcout << std::endl;
}

TEST(test_ac_dat_segment, chinese){
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));

    std::wcout << "\nTest AC Segmentation" << std::endl << std::flush;

    AhoCorasickDoubleArrayTrieSegment ac_segment;
    ac_segment.SetSegAll(false);

    ac_segment.Build("./data/NLP/Dictionary/test_dict_zh.txt", L" ");

    std::wstring sentence(L"我爱北京天安门");

    std::vector<std::wstring> segmented = ac_segment.SegSentence(sentence);

    for(auto & i : segmented){
        std::wcout << i << " " ;
    }
    std::wcout << std::endl;
}

TEST(test_ac_dat_segment, jieba) {
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));

    std::wcout << "\nTest AC DAT Segmentation ZH" << std::endl;

    AhoCorasickDoubleArrayTrieSegment ac_dat_segment;
    ac_dat_segment.SetSegAll(false);

    ac_dat_segment.Build("./data/NLP/Dictionary/jieba_dict.txt.big", L" ");

    std::wstring sentence(L"《三国演义》描写了从东汉末年到西晋初年之间近百年的历史风云，以描写战争为主，诉说了东汉末年的群雄割据混战和魏、蜀、吴三国之间的政治和军事斗争，最终司马炎一统三国，建立晋朝的故事。反映了三国时代各类社会斗争与矛盾的转化，并概括了这一时代的历史巨变，塑造了一群叱咤风云的三国英雄人物。");

    std::vector<std::wstring> segmented = ac_dat_segment.SegSentence(sentence);

    for(auto & i : segmented){
        std::wcout << i << " " ;
    }
    std::wcout << std::endl;
}