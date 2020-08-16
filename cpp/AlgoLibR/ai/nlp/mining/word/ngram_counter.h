/*
 * @Autor: raoqiyu@gmail.com
 * @Date: 2020-08-07 20:20:15
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/ngram_counter.h
 * @Description: 
 */

#ifndef NGRAM_COUNTER_H
#define NGRAM_COUNTER_H

#include <map>
#include <string>
#include <stdlib.h>
#include <vector>
#include <set>
#include <fstream> 
#include "AlgoLibR/data_structure/tree/trie_tree.h"

namespace AlgoLibR{
namespace ai{
namespace nlp{
namespace mining{
namespace word{


class Node{
public:
    wchar_t key;
    unsigned long long value = 0;
    bool is_ending_key;
    std::map<wchar_t, Node*> child_nodes;
    Node *parent;

    Node(const wchar_t key);
    Node(const wchar_t key, Node* parent);
    ~Node();
    void AddChild(const wchar_t key);
    void RemoveChild(const wchar_t key);

};


class NGramCounter : public AlgoLibR::data_structure::tree::trie::Trie<Node>{
public:
    NGramCounter(const unsigned long min_n=2, const unsigned long max_n=3, const wchar_t *delimiters=nullptr);
    void Count(const char *src_fname, const char * dst_fname=nullptr);
    void ExportToFile(const char *dst_fname);
    void Filter(const unsigned long min_freq);


private:
    Node* AddNGram(const wchar_t gram[]);
    void ExportGrams(Node *node, std::wstring gram);
    std::vector<std::wstring> ParseLine(const std::wstring &line);
    
    void Search(Node *node, std::vector<Node*> &leaf_nodes);
    void Delete(Node *node);

    std::wfstream dst_file;
    unsigned long min_n;
    unsigned long max_n;
    std::set<wchar_t> delimiters;
    unsigned long min_freq = 0;
    
};



} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR

#endif