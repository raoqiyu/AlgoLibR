/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-08 19:45:24
 * @FilePath: /AlgoLibR/cpp/test/test_ngrams.cpp
 * @Description: 
 */


#include <iostream>
#include "AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h"

using namespace AlgoLibR::ai::nlp::mining::word;

int main(){
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));
    
    std::wcout << L"开始\n";

    wchar_t *delimiters = L" ，。；‘”’";
    NewWordExtractor ngram_counter = NewWordExtractor(2, 4, delimiters);

    ngram_counter.Extract("../../data/NLP/Corpus/test_for_ngrams.txt");
    ngram_counter.ExportToFile("./ngrams_test_results.txt");
    
    return 0;
}

