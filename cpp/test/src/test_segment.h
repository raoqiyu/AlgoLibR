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
#include<locale>

using namespace AlgoLibR::ai::nlp::seg;

void test_ac_segment(){
    std::cout << "\nTest AC Segmentation" << std::endl;

    AhoCorasickSegment ac_segment;
    ac_segment.SetSegAll(false);

    ac_segment.Build("../../data/NLP/Dictionary/test_dict.txt");

    std::string sentence("Ilovechinachinaloveme");

    std::cout << "Segmentation" << std::endl; 
    std::vector<std::string> segmented = ac_segment.SegSentence(sentence.c_str());
    
    for(auto i = 0; i < segmented.size(); i++){
        std::cout << segmented[i] << " " ;
    }
    std::cout << std::endl;



}
