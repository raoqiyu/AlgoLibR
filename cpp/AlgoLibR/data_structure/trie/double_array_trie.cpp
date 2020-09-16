//
// Created by raoqiyu on 2020/9/16.
//

#include "AlgoLibR/data_structure/trie/double_array_trie.h"

namespace AlgoLibR::data_structure::trie::dat {


DoubleArrayTrie::DoubleArrayTrie() {}
DoubleArrayTrie::~DoubleArrayTrie() {}

void DoubleArrayTrie::setKeys(std::vector<std::wstring> keys){
    this->keys = keys;
}

void DoubleArrayTrie::build(std::vector<std::wstring> keys, std::vector<size_t> values){
    this->keys = keys;
    this->values = values;

    DATNode *root = new DATNode();
    root->depth = 0;
    root->left = 0;
    root->right = keys.size();

    std::vector<DATNode*> siblings;
    fetchSibling(root, siblings);
//    insertSibling(siblings);
}

void DoubleArrayTrie::fetchSibling(DATNode *node, std::vector<DATNode*> &siblings){
    auto target_depth = node->depth;
    wchar_t chr, last_char='\0';
    uint16_t chr_id;
    for(auto i = node->left; i < node->right; i++){
        if(keys[i].size() < target_depth) continue;

        chr = keys[i][target_depth];

        if(chr == last_char) continue;
        last_char = chr;

        auto chr_iter = char2id.find(chr);
        if(chr_iter == char2id.end()){
            chr_id = char2id.size();
            char2id[chr] = chr_id;
            id2char[chr_id] = chr;
        }else{
            chr_id = char2id[chr];
        }

        DATNode *sibling = new DATNode();
        sibling->depth = target_depth;
        sibling->chr = chr_id;
        sibling->left = i;
        if(siblings.size() > 0)
            siblings[siblings.size() - 1]->right = i;
        siblings.push_back(sibling);
    }
    if (siblings.size() != 0)
        siblings[siblings.size() - 1]->right = node->right;
}

wchar_t DoubleArrayTrie::getCharById(uint16_t id){
    auto iter = this->id2char.find(id);
    if(this->id2char.end() == iter){
        return '\0';
    }else{
        return iter->second;
    }
}

} // namespace