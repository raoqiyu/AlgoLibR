/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-08-13 23:07:33
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/NewWordExtractor.cpp
 * @Description: 
 */

#include <math.h>
#include "AlgoLibR/ai/nlp/mining/word/NewWordExtractor.h"
#include "AlgoLibR/framework/logging.h"

namespace AlgoLibR {
namespace ai {
namespace nlp {
namespace mining {
namespace word {

NewWordExtractor::NewWordExtractor(uint8_t max_word_length, unsigned long long min_freq) :
        NGramCounter(1, max_word_length + 1, nullptr), m_min_freq(min_freq) {}

void NewWordExtractor::AddNGram(const wchar_t gram[], Node **start_char_ptr, Node **ending_char_ptr){
    size_t gram_len = wcslen(gram);
    if(gram_len <= 0){
        return;
    }

    Node* p  = this->root;
    for(size_t i = 0; i < gram_len; i++){
        p->AddChild(gram[i]);
        p = p->child_nodes[gram[i]];
    }
    p->value += 1;
    p->is_ending_key=true;

    *start_char_ptr = this->root->child_nodes[gram[0]];
    *ending_char_ptr = p;
}

inline void NewWordExtractor::AddBeginWord(std::wstring &line) {
    const unsigned long start_pos = 0;
    bool is_ok = true;
    Node *start_char_ptr, *ending_char_ptr;
    for (auto k = 0; k < this->min_n; k++) {
        if (line[start_pos + k] == '*') {
            is_ok = false;
            break;
        }
    }
    if (is_ok) {
        NGramCounter::AddNGram(line.substr(start_pos, 1).c_str());
        for (auto k = 1; k < this->max_n - 1; k++) {
            if (start_pos + k >= line.size()) return;
            if (line[start_pos + k] == '*') return;
            AddNGram(line.substr(start_pos, k + 1).c_str(), &start_char_ptr, &ending_char_ptr);
            this->start_char_count[line[start_pos]]++;
            this->end_char_count[line[start_pos+k]]++;
            auto iter = this->m_words.find(ending_char_ptr);
            if (iter == this->m_words.end()) {
                WordNeighbor word;
                word.start_char_ptr = start_char_ptr;
                word.word_length = k+1;
                this->m_words.emplace(ending_char_ptr, word);
            }
        }
//        if (start_pos + this->max_n >= line.size()) return;
        if (line[start_pos + this->max_n-1] == '*') return;
        NGramCounter::AddNGram(line.substr(start_pos, this->max_n).c_str());
//        this->start_char_count[line[start_pos]]++;
//        this->end_char_count[line[start_pos+this->max_n-1]]++;
    }
}

inline void NewWordExtractor::AddWord(std::wstring &line, unsigned long start_pos, unsigned long n_end) {
    bool is_ok = true;
    uint8_t n;
    Node *start_char_ptr, *ending_char_ptr;
    for (n = 0; n < this->min_n; n++) {
        if (line[start_pos + n] == '*') {
            is_ok = false;
            break;
        }
    }
    if (is_ok) {
        auto n_end_bak = n_end;
        if (n_end == this->max_n) {
            n_end--;
        }
        std::map<Node *, WordNeighbor>::iterator word_iter;
        std::map<wchar_t, u_long>::iterator char_iter;
        NGramCounter::AddNGram(line.substr(start_pos, 1).c_str());
        for (n = 1; n < n_end; n++) {
//            if (start_pos + n >= line.size()) return;
//            std::wcout << line[start_pos-1] << std::endl;
            if (line[start_pos + n] == L'*') return;
            //  1 2 3 4
            //  2 3 4 5
            AddNGram(line.substr(start_pos, n + 1).c_str(), &start_char_ptr, &ending_char_ptr);
            this->start_char_count[line[start_pos]]++;
            this->end_char_count[line[start_pos+n]]++;
            word_iter = this->m_words.find(ending_char_ptr);
            if (word_iter == this->m_words.end()) {
                WordNeighbor word;
                word.start_char_ptr = start_char_ptr;
                word.word_length=n+1;
                word.left_neighbors.emplace(line[start_pos - 1], 1);
                this->m_words.emplace(ending_char_ptr, word);
            } else {
                char_iter = word_iter->second.left_neighbors.find(line[start_pos - 1]);
                word_iter->second.left_neighbors[line[start_pos-1]] += 1;
//                if (char_iter == word_iter->second.left_neighbors.end()) {
//                    word_iter->second.left_neighbors.emplace(line[start_pos - 1], 1);
//                } else {
//                    char_iter->second += 1;
//                }
            }
        }
        if (n_end_bak == this->max_n) {
//            if (start_pos + n_end-1 >= line.size()) return;
            if (line[start_pos + n] == '*') return;
            NGramCounter::AddNGram(line.substr(start_pos, n+1).c_str());
//            this->start_char_count[line[start_pos]]++;
//            this->end_char_count[line[start_pos+n]]++;
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
    std::wstring line;
    std::wstring gram_str;
    unsigned long start_pos, split_pos;
    uint8_t k = this->max_n;
    while (std::getline(src_file, line)) {
        if (line.size() < this->min_n) continue;
        line = std::regex_replace(line, this->delimiters, L"*");
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

inline void NewWordExtractor::CalcEntropyScore(const std::map<Node *, WordNeighbor>::iterator &word_iter) {
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


void NewWordExtractor::CalcPointMutalInformation(const std::map<Node *, WordNeighbor>::iterator &word_iter,
                                                 std::map<uint8_t, u_long> &ngram_count) {
    double joint_prob, independent_prob=1;

    joint_prob = double(word_iter->first->value)/ngram_count[word_iter->second.word_length];
    Node* node = word_iter->first;
    while(node != this->root){
        independent_prob *= double(node->value)/ngram_count[1];
        node = node->parent;
    }
    word_iter->second.score += log2(joint_prob/independent_prob)/word_iter->second.word_length;
}

void NewWordExtractor::CalcScore() {
    std::wstring word;
    auto word_iter = this->m_words.begin();
    std::map<uint8_t, u_long> ngram_count;
    while (word_iter != this->m_words.end()) {
        CalcEntropyScore(word_iter);
        ++ngram_count[word_iter->second.word_length];
        word_iter++;
    }
    ngram_count[1] = this->root->child_nodes.size();
    for (word_iter = this->m_words.begin(); word_iter != this->m_words.end(); word_iter++) {
        CalcPointMutalInformation(word_iter, ngram_count);
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
//    std::map<wchar_t, u_long> start_char_count;
//    std::map<wchar_t, u_long> end_char_count;
    while (word_iter != this->m_words.end()) {
        if (word_iter->first->value < this->m_min_freq) {
            this->m_words.erase(word_iter++);
        } else {
//            ++end_char_count[word_iter->first->key];
            word_iter++;
        }
    }
//    for (auto node : this->root->child_nodes) {
//        start_char_count[node.second->key] = node.second->value;
//    }
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
    word_iter = this->m_words.begin();
    while (word_iter != this->m_words.end()) {
        if ((invalid_end_chars.end() != invalid_end_chars.find(word_iter->first->key)) or (
            invalid_start_chars.end() != invalid_start_chars.find(word_iter->second.start_char_ptr->key))) {
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