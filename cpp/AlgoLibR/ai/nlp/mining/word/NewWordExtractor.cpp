/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-13 23:07:33
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/NewWordExtractor.cpp
 * @Description: 
 */


#include <map>
#include <string>
#include <stdlib.h>
#include <vector>
#include <set>
#include <fstream>

#include "AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h"

namespace AlgoLibR {
namespace ai {
namespace nlp {
namespace mining {
namespace word {

NewWordExtractor::NewWordExtractor(unsigned long min_n, unsigned long max_n,
                                   const wchar_t *delimiters) : NGramCounter(min_n, max_n + 1, delimiters) {}

void NewWordExtractor::Extract(const char *src_fname) {
    std::wifstream src_file(src_fname);
    if (!src_file.is_open()) {
        std::wcout << src_fname << L" 文件打开失败..." << std::endl;
        return;
    }
    std::wstring line;
    Node *last_wchar_ptr;
    wchar_t left_wchar;
    std::wstring gram_str;
    while (std::getline(src_file, line)) {
        line.insert(0, 1, L'S');
        for (auto gram : ParseLine(line)) {
            left_wchar = gram[0];
            gram_str = gram.substr(1);
            last_wchar_ptr = AddNGram(gram_str.c_str());

            std::wcout << left_wchar << " : " << gram_str << std::endl;
            auto iter = this->m_words.find(last_wchar_ptr);
            if (iter == this->m_words.end()) {
                WordNeighbor word(last_wchar_ptr);
                word.left_neighbors.insert(left_wchar);
                this->m_words.emplace(last_wchar_ptr, word);
            } else {
                iter->second.left_neighbors.insert(left_wchar);
            }

        }
    }
    for (auto word : this->m_words) {
        std::wcout << word.second.last_wchar_ptr->key << ", left neighbors: ";
        for (auto c : word.second.left_neighbors) {
            std::wcout << c << " ";
        }
        std::wcout << '\n';
    }

    src_file.close();
}

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR