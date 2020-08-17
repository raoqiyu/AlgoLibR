/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-13 23:07:33
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/NewWordExtractor.cpp
 * @Description: 
 */


#include "AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h"

namespace AlgoLibR {
namespace ai {
namespace nlp {
namespace mining {
namespace word {

NewWordExtractor::NewWordExtractor(unsigned long min_n, unsigned long max_n,
                                   const wchar_t *delimiters) : NGramCounter(min_n, max_n, delimiters) {}

inline void NewWordExtractor::AddBeginWord(std::wstring &line) {
    const unsigned long start_pos = 0;
    bool is_ok = true;
    Node *last_wchar_ptr;
    for (auto k = 0; k < this->min_n; k++) {
        if (delimiters.find(line[start_pos + k]) != delimiters.end()) {
            is_ok = false;
            break;
        }
    }
    if (is_ok) {
        for (auto k = this->min_n - 1; k < this->max_n; k++) {
            if (delimiters.find(line[start_pos + k]) != delimiters.end()) break;
            last_wchar_ptr = AddNGram(line.substr(start_pos, k + 1).c_str());
            auto iter = this->m_words.find(last_wchar_ptr);
            if (iter == this->m_words.end()) {
                WordNeighbor word(last_wchar_ptr);
                this->m_words.emplace(last_wchar_ptr, word);
            }
        }
    }
}

inline void NewWordExtractor::AddWord(std::wstring &line, const unsigned long start_pos, const unsigned long n_end) {
    bool is_ok = true;
    Node *last_wchar_ptr;
    unsigned long n;
    for (n = 0; n < this->min_n; n++) {
        if (delimiters.find(line[start_pos + n]) != delimiters.end()) {
            is_ok = false;
            break;
        }
    }
    if (is_ok) {
        for (n = this->min_n - 1; n < n_end; n++) {
            if (delimiters.find(line[start_pos + n]) != delimiters.end()) break;
            last_wchar_ptr = AddNGram(line.substr(start_pos, n + 1).c_str());
            auto iter = this->m_words.find(last_wchar_ptr);
            if (iter == this->m_words.end()) {
                WordNeighbor word(last_wchar_ptr);
                word.left_neighbors.insert(line[start_pos - 1]);
                this->m_words.emplace(last_wchar_ptr, word);
            } else {
                iter->second.left_neighbors.insert(line[start_pos - 1]);
            }
        }
    }
}

void NewWordExtractor::Extract(const char *src_fname) {
    std::wifstream src_file(src_fname);
    if (!src_file.is_open()) {
        std::wcout << src_fname << L" 文件打开失败..." << std::endl;
        return;
    }

    std::wstring line;
    std::wstring gram_str;
    unsigned long start_pos, k = this->max_n;
    while (std::getline(src_file, line)) {
        if (line.size() < this->min_n) continue;
        AddBeginWord(line);
        for (start_pos = 1; start_pos < line.size() - this->max_n; start_pos++) {
            AddWord(line, start_pos, this->max_n);
        }
        for (start_pos = line.size() - k; start_pos < line.size() && k > 0; start_pos++, k--) {
            AddWord(line, start_pos, k);
        }
    }

}

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR