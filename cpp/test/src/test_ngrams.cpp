/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-08 19:45:24
 * @FilePath: /AlgoLibR/cpp/test/test_ngrams.cpp
 * @Description: 
 */


#include <iostream>
#include <gtest/gtest.h>

#include "AlgoLibR/framework/logging.h"
#include "AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h"

using namespace AlgoLibR::ai::nlp::mining::word;

TEST(test_ngram_fn, test_ngram){
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));


    AlgoLibR::LOGGING_INFO(L"开始");

    NewWordExtractor ngram_counter = NewWordExtractor(5,2);

    ngram_counter.Extract("../../../data/NLP/Corpus/test_for_ngrams_bak.txt");
    ngram_counter.ExportToFile("./ngrams_test_results.txt");
    time(&timep);
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    AlgoLibR::LOGGING_INFO(L"结束");
    EXPECT_EQ(3, 3);

}

