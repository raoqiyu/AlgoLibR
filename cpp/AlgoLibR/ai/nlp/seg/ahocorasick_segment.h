/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-17 11:00:48
FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/seg/ahocorasick_segment.h
 * @Description: 
 */

#ifndef AI_SEG_AC_H
#define AI_SEG_AC_H

#include <vector>
#include <string>
#include "AlgoLibR/data_structure/tree/ac_trie.h"

namespace AlgoLibR{
namespace ai{
namespace nlp{
namespace seg{

class WordProp{
public:
    unsigned int word_length;
    size_t freq;
    char* nature;
    
    WordProp();
    WordProp(const WordProp& other);
    WordProp& operator=(const WordProp& other);
    WordProp(const char nature[], const size_t freq, const unsigned int length);
    ~WordProp();
};

class ACSegNode{
public:
    wchar_t key;
    bool is_ending_key;
    WordProp* word_prop;

    ACSegNode *parent=NULL;
    ACSegNode *failure=NULL;
    std::map<wchar_t, ACSegNode*> child_nodes;

    ~ACSegNode();
    ACSegNode(const wchar_t key);
    ACSegNode(const wchar_t key, ACSegNode* parent);
    void AddChild(const wchar_t key);
    void RemoveChild(const wchar_t key);    
};


class AhoCorasickSegment : public AlgoLibR::data_structure::tree::ac_trie::ACTrieBase<ACSegNode>{
private:
    bool is_seg_all;

private:
    std::size_t GetKeySizeFromNode(const ACSegNode *p);
    void CollectKeySizesFromNode(const ACSegNode *p, int pos, std::map<size_t,std::vector<WordProp>> &dag);
    void ExtractDAG(const wchar_t sentence[], std::map<size_t,std::vector<WordProp>> &dag);

public:
    AhoCorasickSegment();
    void AddWord(const wchar_t word[], const char nature[], const size_t freq);
    void SetSegAll(bool is_seg_all);
    void Build(const char dictionary_fname[],  const std::wstring& delimiters);
    std::vector<std::wstring> SegSentence(const wchar_t sentence[]);
    // std::vector<std::wstring> SegChineseSentence(const wchar_t sentence[]);

};


} // namespace seg
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR


#endif
