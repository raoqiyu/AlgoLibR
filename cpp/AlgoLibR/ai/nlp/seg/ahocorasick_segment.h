/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-17 11:00:48
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/seg/ahocorasick_segment.h
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
    char key;
    bool is_ending_key;
    WordProp* word_prop;

    ACSegNode *parent=NULL;
    ACSegNode *failure=NULL;
    std::map<char, ACSegNode*> child_nodes;

    ~ACSegNode();
    ACSegNode(const char key);
    ACSegNode(const char key, ACSegNode* parent);
    void AddChild(const char key);
    void RemoveChild(const char key);    
};


class AhoCorasickSegment : public AlgoLibR::data_structure::tree::ac_trie::ACTrieBase<ACSegNode>{
private:
    bool is_seg_all;

private:
    std::vector<std::string> SegAll(const char sentence[]);
    std::size_t GetKeySizeFromNode(const ACSegNode *p);
    void CollectKeySizesFromNode(const ACSegNode *p, int pos, std::map<size_t,std::vector<WordProp>> &dag);
    void ExtractDAG(const char sentence[], std::map<size_t,std::vector<WordProp>> &dag);

public:
    AhoCorasickSegment();
    void AddWord(const char word[], const char nature[], const size_t freq);
    void SetSegAll(bool is_seg_all);
    void Build(const char dictionary_fname[]);
    std::vector<std::string> SegSentence(const char sentence[]);
    std::vector<std::wstring> SegChineseSentence(const char sentence[]);

};


} // namespace seg
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR


#endif
