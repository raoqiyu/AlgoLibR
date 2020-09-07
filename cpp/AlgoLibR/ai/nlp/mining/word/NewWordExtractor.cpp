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
        NGramCounter(1, max_word_length + 1, nullptr), m_min_freq(min_freq) {}

void NewWordExtractor::AddWord(std::wstring &str, ulong start_pos, uint8_t word_size){
    Node* p  = this->root;
    for(size_t i = 0; i < word_size; i++){
        p = p->AddChildPtr(str[start_pos+i]);
    }
    p->value += 1;
    p->is_ending_key=true;
}

void NewWordExtractor::AddWord(std::wstring &str, ulong start_pos, uint8_t word_size, Node **start_char_ptr, Node **ending_char_ptr){
    Node* p  = this->root;
    for(size_t i = 0; i < word_size; i++){
        p = p->AddChildPtr(str[start_pos+i]);
    }
    p->value += 1;
    p->is_ending_key=true;
    *start_char_ptr = this->root->child_nodes[str[start_pos]];
    *ending_char_ptr = p;
}


inline void NewWordExtractor::AddBeginWords(std::wstring &line) {
    const unsigned long start_pos = 0;
    bool is_ok = true;
    Node *start_char_ptr, *ending_char_ptr;
    AddWord(line, start_pos, 1);
    for (auto k = 2; k < this->max_n; k++) {
        AddWord(line, start_pos, k, &start_char_ptr, &ending_char_ptr);
        this->start_char_count[line[start_pos]]++;
        this->end_char_count[line[start_pos+k-1]]++;
        auto iter = this->m_words.find(ending_char_ptr);
        if (iter == this->m_words.end()) {
            WordNeighbor word;
            word.start_char_ptr = start_char_ptr;
            word.word_length = k;
            this->m_words.emplace(ending_char_ptr, word);
        }
    }

    AddWord(line, start_pos, this->max_n);
}

inline void NewWordExtractor::AddWords(std::wstring &line, unsigned long start_pos, unsigned long n_end) {
    bool is_ok = true;
    Node *start_char_ptr, *ending_char_ptr;
    auto n_end_bak = n_end;
    if (n_end == this->max_n) {
        AddWord(line, start_pos, n_end);
        n_end--;
    }
    std::unordered_map<Node *, WordNeighbor>::iterator word_iter;
    std::unordered_map<wchar_t, u_long>::iterator char_iter;
    AddWord(line, start_pos, 1);
    for (auto k = 2; k <= n_end; k++) {
        //  1 2 3 4
        //  2 3 4 5
        AddWord(line, start_pos, k, &start_char_ptr, &ending_char_ptr);
        this->start_char_count[line[start_pos]]++;
        this->end_char_count[line[start_pos+k-1]]++;
        word_iter = this->m_words.find(ending_char_ptr);
        if (word_iter == this->m_words.end()) {
            WordNeighbor word;
            word.start_char_ptr = start_char_ptr;
            word.word_length=k;
            word.left_neighbors.emplace(line[start_pos - 1], 1);
            this->m_words.emplace(ending_char_ptr, word);
        } else {
            char_iter = word_iter->second.left_neighbors.find(line[start_pos - 1]);
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
    uint8_t k = this->max_n;
    std::vector<std::wstring> sub_lines;
    while (std::getline(src_file, raw_line)) {
        sub_lines.clear();

        if (raw_line.size() < this->min_n){
            raw_line.clear();
            continue;
        }

        raw_line = std::regex_replace(raw_line, this->delimiters, L"*");
        if(raw_line.size() < this->min_n or raw_line[0] == L'*'){
            raw_line.clear();
            continue;
        }

        AlgoLibR::framework::string::split(raw_line, sub_lines, L"*");
        for(auto i = 0; i < sub_lines.size(); i++){
            line = sub_lines[i];
            if (line.size() < this->min_n) continue;
            AddBeginWords(line);
            split_pos = std::max((long) (line.size() - this->max_n), 0L);
            for (start_pos = 1; start_pos < split_pos; start_pos++) {
                AddWords(line, start_pos, this->max_n);
            }
            for (start_pos = split_pos; start_pos < line.size() && k > 0; start_pos++, k--) {
                AddWords(line, start_pos, k);
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
    std::vector<std::pair<Node *, WordNeighbor>> vec(this->m_words.begin(), this->m_words.end());
    std::sort(vec.begin(), vec.end(), WordCmp);
    for (int i = 0; i < 200; ++i) {
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


void NewWordExtractor::CalcPointMutalInformation(const std::unordered_map<Node *, WordNeighbor>::iterator &word_iter) {
    double joint_prob, independent_prob=1;

    joint_prob = double(word_iter->first->value)/this->ngram_count[word_iter->second.word_length];
    Node* node = word_iter->first;
    while(node != this->root){
        independent_prob *= double(node->value)/this->ngram_count[1];
        node = node->parent;
    }
    word_iter->second.score += log2(joint_prob/independent_prob)/word_iter->second.word_length;
}

void NewWordExtractor::CalcScore() {
    std::wstring word;
    auto word_iter = this->m_words.begin();
    while (word_iter != this->m_words.end()) {
        CalcEntropyScore(word_iter);
        CalcPointMutalInformation(word_iter);
        word_iter++;
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
    auto word_iter = this->m_words.begin();
    while (word_iter != this->m_words.end()) {
        if (word_iter->first->value < this->m_min_freq) {
            this->m_words.erase(word_iter++);
        } else {
            ++this->ngram_count[word_iter->second.word_length];
            word_iter++;
        }
    }
    this->ngram_count[1] = 0;
    for(auto child_node : this->root->child_nodes){
        if(child_node.second->value < this->m_min_freq) continue;
        this->ngram_count[1] += child_node.second->value;
    }
    uint threshold = uint(this->m_words.size() * 0.004);
    threshold = std::max(uint(50), threshold);
    std::set<wchar_t> invalid_start_chars, invalid_end_chars;
    for (auto char_cnt : this->start_char_count) {
        if (char_cnt.second <= threshold) continue;
        invalid_start_chars.insert(char_cnt.first);
    }
    for (auto char_cnt : this->end_char_count) {
        if (char_cnt.second <= threshold) continue;
        invalid_end_chars.insert(char_cnt.first);
    }

    this->start_char_count.clear();
    this->end_char_count.clear();

    word_iter = this->m_words.begin();
    while (word_iter != this->m_words.end()) {
        if ((invalid_end_chars.end() != invalid_end_chars.find(word_iter->first->key)) or (
            invalid_start_chars.end() != invalid_start_chars.find(word_iter->second.start_char_ptr->key))) {
            --this->ngram_count[word_iter->second.word_length];
            this->m_words.erase(word_iter++);
            continue;
        }
        word_iter++;
    }
}

} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR