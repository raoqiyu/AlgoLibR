/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-13 23:07:33
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/NewWordExtractor.cpp
 * @Description: 
 */

#include <math.h>
#include "AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h"

namespace AlgoLibR {
namespace ai {
namespace nlp {
namespace mining {
namespace word {

NewWordExtractor::NewWordExtractor(uint8_t max_word_length) : NGramCounter(1, max_word_length + 1, nullptr) {}

inline void NewWordExtractor::AddBeginWord(std::wstring &line) {
    const unsigned long start_pos = 0;
    bool is_ok = true;
    Node *last_wchar_ptr;
    for (auto k = 0; k < this->min_n; k++) {
        if (line[start_pos + k] == '*') {
            is_ok = false;
            break;
        }
    }
    if (is_ok) {
        for (auto k = this->min_n; k < this->max_n - 1; k++) {
            if (start_pos + k >= line.size()) break;
            if (line[start_pos + k] == '*') break;
            last_wchar_ptr = AddNGram(line.substr(start_pos, k + 1).c_str());
            auto iter = this->m_words.find(last_wchar_ptr);
            if (iter == this->m_words.end()) {
                WordNeighbor word;
                word.last_char_ptr = last_wchar_ptr;
                this->m_words.emplace(last_wchar_ptr, word);
            }
        }
        if (start_pos + this->max_n >= line.size()) return;
        if (line[start_pos + this->max_n] == '*') return;
        last_wchar_ptr = AddNGram(line.substr(start_pos, this->max_n).c_str());
    }
}

inline void NewWordExtractor::AddWord(std::wstring &line, const unsigned long start_pos, const unsigned long n_end) {
    bool is_ok = true;
    Node *last_wchar_ptr;
    uint8_t n;
    for (n = 0; n < this->min_n; n++) {
        if (line[start_pos + n] == '*') {
            is_ok = false;
            break;
        }
    }
    if (is_ok) {
        unsigned long word_n_end = n_end;
        if (word_n_end == this->max_n) {
            word_n_end--;
        }
        std::map<Node *, WordNeighbor>::iterator word_iter;
        std::map<wchar_t, u_long>::iterator char_iter;
        for (n = this->min_n; n < word_n_end; n++) {
            if (start_pos + n >= line.size()) return;
//            std::wcout << line[start_pos-1] << std::endl;
            if (line[start_pos + n] == L'*') return;
            last_wchar_ptr = AddNGram(line.substr(start_pos, n + 1).c_str());
            word_iter = this->m_words.find(last_wchar_ptr);
            if (word_iter == this->m_words.end()) {
                WordNeighbor word;
                word.last_char_ptr = last_wchar_ptr;
                word.left_neighbors.emplace(line[start_pos - 1], 1);
                this->m_words.emplace(last_wchar_ptr, word);
            } else {
                char_iter = word_iter->second.left_neighbors.find(line[start_pos - 1]);
                if (char_iter == word_iter->second.left_neighbors.end()) {
                    word_iter->second.left_neighbors.emplace(line[start_pos - 1], 1);
                } else {
                    char_iter->second += 1;
                }
            }
        }
        if (n_end == this->max_n) {
            if (start_pos + n_end >= line.size()) return;
            if (line[start_pos + n_end] == '*') return;
            last_wchar_ptr = AddNGram(line.substr(start_pos, n_end).c_str());
        }
    }
}

bool WordCmp(const std::pair<Node *, WordNeighbor> &a, const std::pair<Node *, WordNeighbor> &b) {
    return a.second.score > b.second.score;
};

void NewWordExtractor::Extract(const char *src_fname) {
    std::wifstream src_file(src_fname);
    if (!src_file.is_open()) {
        std::wcout << src_fname << L" 文件打开失败..." << std::endl;
        return;
    }

    std::wstring line;
    std::wstring gram_str;
    unsigned long start_pos, split_pos;
    uint8_t k = this->max_n;
    while (std::getline(src_file, line)) {
        if (line.size() < this->min_n) continue;
        line = std::regex_replace(line, this->delimiters, L"*");
        std::wcout << line << std::endl;
        AddBeginWord(line);
        split_pos = std::max((long) (line.size() - this->max_n), 0L);
//        std::wcout << split_pos << ':' << line[split_pos] <<  std::endl;
        for (start_pos = 1; start_pos < split_pos; start_pos++) {
            AddWord(line, start_pos, this->max_n);
        }
        for (start_pos = split_pos; start_pos < line.size() && k > 0; start_pos++, k--) {
            AddWord(line, start_pos, k);
        }
        line.clear();
    }

    CalcScore();

    // Sort by score
    std::wstring word;
    std::vector<std::pair<Node *, WordNeighbor>> vec(this->m_words.begin(), this->m_words.end());
    std::sort(vec.begin(), vec.end(), WordCmp);
    for (int i = 0; i < vec.size(); ++i) {
        GetWord(vec[i].first, word);
        std::wcout << word << " : " << vec[i].second.score << std::endl;
        word.clear();
    }

}

void NewWordExtractor::GetWord(Node *node, std::wstring &word) {
    if (node == this->root) {
        reverse(word.begin(), word.end());
        return;
    }
    word.push_back(node->key);
    GetWord(node->parent, word);
}

inline void NewWordExtractor::CalcEntropyScore(const std::map<Node *, WordNeighbor>::iterator &word_iter) {
    long double left_total_cnt = 0, right_total_cnt = 0;
//    std::wcout << "left: ";
    for (auto left_char : word_iter->second.left_neighbors) {
//        std::wcout << "(" << left_char.first << ':' << left_char.second << ") ";
        left_total_cnt += left_char.second;
    }
//    std::wcout << std::endl << "right: ";
    double left_entropy = 1e-8, right_entropy = 1e-8, prob;
    if (left_total_cnt > 0) {
        for (auto left_char : word_iter->second.left_neighbors) {
            prob = left_char.second / left_total_cnt;
            left_entropy -= prob * log2(prob);
        }
    }

    for (auto child_node : word_iter->first->child_nodes) {
//        std::wcout << "(" << child_node.first << ':' << child_node.second->value << ") ";
        right_total_cnt += child_node.second->value;
    }
//    std::wcout << std::endl << std::flush;
    if (right_total_cnt > 0) {
        for (auto child_node : word_iter->first->child_nodes) {
            prob = child_node.second->value / right_total_cnt;
//            std::wcout << prob << ',' << child_node.second->value << ',' << right_total_cnt << std::endl;
            right_entropy -= prob * log2(prob);
        }
    }
    word_iter->second.score = log2((left_entropy * exp(right_entropy) +
        right_entropy * exp(left_entropy)) / (abs(left_entropy - right_entropy) + 1e-8));
//    std::wcout << left_total_cnt << ',' << left_entropy << ';' << right_total_cnt << ',' << right_entropy << std::endl;
}

void NewWordExtractor::CalcScore() {
    std::wstring word;
    for (auto word_iter = this->m_words.begin(); word_iter != this->m_words.end(); word_iter++) {
        CalcEntropyScore(word_iter);
    }
    std::wcout << std::flush;
}

void NewWordExtractor::CalcPointMutalInformation() {
    return;
}

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR