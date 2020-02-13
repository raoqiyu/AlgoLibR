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

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace kv_trie{


template<class T>
class KVTrieNode{
public:
    char key;
    T value;
    bool is_ending_char;
    std::map<char, KVTrieNode*> child_nodes;
    KVTrieNode *parent;

    KVTrieNode(const char key);
    KVTrieNode(const char key, KVTrieNode* parent);
    ~KVTrieNode();
    void AddChild(const char key);
    void RemoveChild(const char key);
};

template<class T>
class KVTrie{
private:
    KVTrieNode<T> *root;

public:
    KVTrie();
    ~KVTrie();

    void Add(const char key[], const T value);
    KVTrieNode<T>* FindNode(const char key[]);
    bool Search(const char key[], T &value);
    void Remove(const char key[]);
};

} // namespace kv_trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR

#endif
