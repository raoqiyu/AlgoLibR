/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-13 23:07:33
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/NewWordExtractor.cpp
 * @Description: 
 */

#include <math.h>
#include "AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h"
#include "AlgoLibR/framework/logging.h"
#include "AlgoLibR/framework/string.h"

namespace AlgoLibR {
namespace ai {
namespace nlp {
namespace mining {
namespace word {

NewWordExtractor::NewWordExtractor(uint8_t max_word_length, unsigned long long min_freq) :
        NGramCounter(1, max_word_length + 1, nullptr), m_min_freq(min_freq) {
    for(auto k = 2; k <= max_word_length; k++){
        this->m_words.emplace(k, std::unordered_map<Node *, WordNeighbor>());
    }
}

void NewWordExtractor::AddWord(std::wstring &str, u_long start_pos, uint8_t word_size){
    Node* p  = this->root;
    for(size_t i = 0; i < word_size; i++){
        p = p->AddChildPtr(str[start_pos+i]);
    }
    p->value += 1;
    p->is_ending_key=true;
}

void NewWordExtractor::AddWord(std::wstring &str, u_long start_pos, uint8_t word_size, Node **ending_char_ptr){
    Node* p  = this->root;
    for(size_t i = 0; i < word_size; i++){
        p = p->AddChildPtr(str[start_pos+i]);
    }
    p->value += 1;
    p->is_ending_key=true;
    *ending_char_ptr = p;
}

inline void NewWordExtractor::AddWord(wchar_t chr, Node **last_char_ptr){
    Node* p = *last_char_ptr;
    p = p->AddChildPtr(chr);
    p->value += 1;
    p->is_ending_key=true;
    *last_char_ptr = p;
}



inline void NewWordExtractor::AddBeginWords(std::wstring &line) {
    const unsigned long start_pos = 0, n = std::min(line.size(), (size_t)this->max_n-1);
    Node *ending_char_ptr;
    this->start_char_count[line[start_pos]] += n-1;
    AddWord(line, start_pos, 1, &ending_char_ptr);
    for (auto k = 2; k <= n; k++) {
        AddWord(line[start_pos+k-1], &ending_char_ptr);
        this->end_char_count[line[start_pos+k-1]]++;
        auto iter = this->m_words[k].find(ending_char_ptr);
        if (iter == this->m_words[k].end()) {
            WordNeighbor word;
            word.start_char = line[start_pos];
            this->m_words[k].emplace(ending_char_ptr, word);
        }
    }
    if (line.size() >= this->max_n) AddWord(line[start_pos+this->max_n-1], &ending_char_ptr);
}

inline void NewWordExtractor::AddWords(std::wstring &line, unsigned long start_pos, unsigned long n_end) {
    Node *ending_char_ptr;
    std::unordered_map<Node *, WordNeighbor>::iterator word_iter;
//    std::unordered_map<wchar_t, u_long>::iterator char_iter;
    this->start_char_count[line[start_pos]] += n_end-1;
    if (n_end == this->max_n) this->start_char_count[line[start_pos]]--;
    AddWord(line, start_pos, 1, &ending_char_ptr);
    for (auto k = 2; k <= n_end; k++) {
        //  1 2 3 4
        //  2 3 4 5
        AddWord(line[start_pos+k-1], &ending_char_ptr);
        this->end_char_count[line[start_pos+k-1]]++;
        word_iter = this->m_words[k].find(ending_char_ptr);
        if (word_iter == this->m_words[k].end()) {
            WordNeighbor word;
            word.start_char = line[start_pos];
            word.left_neighbors.emplace(line[start_pos - 1], 1);
            this->m_words[k].emplace(ending_char_ptr, word);
        } else {
            word_iter->second.left_neighbors[line[start_pos-1]] += 1;
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
    AlgoLibR::LOGGING_INFO(L"读取文件");
    std::wstring line, raw_line;
    std::wstring gram_str;
    unsigned long start_pos, split_pos;
    uint8_t k;
    std::vector<std::wstring> sub_lines;
    while (std::getline(src_file, raw_line)) {
        sub_lines.clear();

        if (raw_line.size() < this->min_n){
            raw_line.clear();
            continue;
        }

        raw_line = std::regex_replace(raw_line, this->delimiters, L"*");
        AlgoLibR::framework::string::split(raw_line, sub_lines, L"*");
        for(auto i = 0; i < sub_lines.size(); i++){
            line = sub_lines[i];
//            AlgoLibR::LOGGING_INFO(L"%ls", sub_lines[i].c_str());
            if (line.size() < this->min_n) continue;
            AddBeginWords(line);
            if(line.size() - 1 >= this->max_n){
                split_pos = line.size() - 1 - this->max_n;
                k = this->max_n;
                for (start_pos = 1; start_pos <= split_pos; start_pos++) {
                    AddWords(line, start_pos, this->max_n);
                }
                for (start_pos = split_pos+1; start_pos < line.size() && k > 0; start_pos++, k--) {
                    AddWords(line, start_pos, k);
                }
            }else{
                k = line.size() - 1;
                for (start_pos = 1; start_pos < line.size() && k > 0; start_pos++, k--) {
                    AddWords(line, start_pos, k);
                }
            }
        }
        raw_line.clear();
        sub_lines.clear();
    }
    AlgoLibR::LOGGING_INFO(L"过滤低频词汇、高频开始和结束字的词汇");
    Filter();

    AlgoLibR::LOGGING_INFO(L"计算分数");
    CalcScore();

    AlgoLibR::LOGGING_INFO(L"排序");
    // Sort by score
    std::wstring word;
    std::vector<std::pair<Node *, WordNeighbor>> vec;
    for(auto k = 2; k < this->max_n; k++){
        for(const auto& item : this->m_words[k]){
            vec.emplace_back(item);
        }
    }
    std::sort(vec.begin(), vec.end(), WordCmp);
    for (int i = 0; i < std::min((size_t)200, vec.size()); ++i) {
        GetWord(vec[i].first, word);
        std::wcout << word << " : " << vec[i].second.score << std::endl;
        word.clear();
    }
}

void NewWordExtractor::GetWord(Node *node, std::wstring &word) {
    while(node != this->root){
        word.push_back(node->key);
        node = node->parent;
    }
    std::reverse(word.begin(), word.end());
}

inline void NewWordExtractor::CalcEntropyScore(const std::unordered_map<Node *, WordNeighbor>::iterator &word_iter) {
    long double left_total_cnt = 0, right_total_cnt = 0;
//    std::wcout << "left: ";
    for (auto left_char : word_iter->second.left_neighbors) {
//        std::wcout << "(" << left_char.first << ':' << left_char.second << ") ";
        left_total_cnt += left_char.second;
    }
//    std::wcout << std::endl << "right: ";
    double left_entropy = 0, right_entropy = 0, prob;
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
        right_entropy * exp(left_entropy)+1e-4) / (abs(left_entropy - right_entropy) + 1));
//    std::wcout << left_total_cnt << ',' << left_entropy << ';' << right_total_cnt << ',' << right_entropy << std::endl;
}


inline void NewWordExtractor::CalcPointMutalInformation(const std::unordered_map<Node *, WordNeighbor>::iterator &word_iter,
                                                 const u_long &word_length_count, const u_long &single_char_count,
                                                 uint8_t &word_length) {
    double joint_prob, independent_prob=1;

    joint_prob = double(word_iter->first->value)/word_length_count;
    Node* node = word_iter->first;
    while(node != this->root){
        independent_prob *= double(node->value)/single_char_count;
        node = node->parent;
    }
    word_iter->second.score += log2(joint_prob/independent_prob)/word_length;
}

void NewWordExtractor::CalcScore() {
    u_long single_char_count = 0;
    for(auto child_node : this->root->child_nodes){
        if(child_node.second->value < this->m_min_freq) continue;
        single_char_count += child_node.second->value;
    }
    std::wstring word;
    for(uint8_t  k = 2; k < this->max_n; k++) {
        auto word_iter = this->m_words[k].begin();
        while (word_iter != this->m_words[k].end()) {
            CalcEntropyScore(word_iter);
            CalcPointMutalInformation(word_iter, this->ngram_count[k], single_char_count, k);
            word_iter++;
        }
    }
}

inline wchar_t NewWordExtractor::FindLeadingChar(Node *end_node) {
    wchar_t leading_char('\0');
    if (nullptr == end_node) return leading_char;
    leading_char = end_node->key;
    Node *node = end_node->parent;
    while (node != this->root) {
        leading_char = node->key;
        node = node->parent;
    }
    return leading_char;
}
void NewWordExtractor::Filter() {
    this->m_words.erase(this->max_n);
    u_long threshold = 0;
    for(auto k = 2; k < this->max_n; k++) {
        this->ngram_count[k] = this->m_words[k].size();
        threshold = u_long(this->m_words[k].size()*0.004);
        auto word_iter = this->m_words[k].begin();
        while (word_iter != this->m_words[k].end()) {
            if ((word_iter->first->value < this->m_min_freq) or
                (this->start_char_count[word_iter->second.start_char] > threshold) or
                (this->end_char_count[word_iter->first->key] > threshold)) {
                this->m_words[k].erase(word_iter++);
                continue;
            }
            word_iter++;
        }
    }
    this->start_char_count.clear();
    this->end_char_count.clear();
}

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR