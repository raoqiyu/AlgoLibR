/*
Author: raoqiyu@gmail.com
Date: 2020-02-11 18:34:27
FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/kv_trie_tree.h
Description: 
 */

#ifndef DS_TREE_KVTRIE_H
#define DS_TREE_KVTRIE_H

#include <map>
#include <stdlib.h>
#include "AlgoLibR/data_structure/tree/trie_tree.h"

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace kv_trie{


template<class T>
class KVTrieNode{
public:
    char key;
    T value;
    bool is_ending_key;
    std::map<char, KVTrieNode*> child_nodes;
    KVTrieNode *parent;

    KVTrieNode(const char key);
    KVTrieNode(const char key, KVTrieNode* parent);
    ~KVTrieNode();
    void AddChild(const char key);
    void RemoveChild(const char key);
};

template<typename T>
class KVTrie : public trie::Trie<KVTrieNode<T>>{
public:
    void Add(const char key[], T value);
    bool Search(const char key[], T &value);
};

} // namespace kv_trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR

#endif
