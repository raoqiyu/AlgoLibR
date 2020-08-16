/*
 * @Autor: raoqiyu@gmail.com
 * @Date: 2020-08-08 19:45:24
 * @FilePath: /AlgoLibR/cpp/test/test_ngrams.cpp
 * @Description: 
 */


#include <iostream>
#include "AlgoLibR/ai/nlp/mining/word/ngram_counter.h"

using namespace AlgoLibR::ai::nlp::mining::word;

int main(){
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));
    
    std::wcout << L"开始\n";

    wchar_t *delimiters = L" ，。；‘”’";
    NGramCounter ngram_counter = NGramCounter(3, 4, delimiters);

    ngram_counter.Count("../../data/NLP/Corpus/test_for_ngrams.txt");
    ngram_counter.ExportToFile("./ngrams_test_results.txt");

    ngram_counter.Filter(2);
    ngram_counter.ExportToFile("./ngrams_test_results_filtered.txt");
    
    
    return 0;
}

