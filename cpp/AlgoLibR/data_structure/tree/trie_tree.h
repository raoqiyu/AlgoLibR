/*
Author: raoqiyu@gmail.com
Date: 2020-02-11 18:34:27
FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/trie_tree.h
Description: 
 */

#ifndef DS_TREE_TRIE_H
#define DS_TREE_TRIE_H

#include <map>
#include <stdlib.h>

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace trie{

const int kTrieCharCount = 26;

template<class T>
class TrieNode{
public:
    T value;
    bool is_ending_char;
    std::map<char, TrieNode*> child_nodes;
    TrieNode *parent;

    TrieNode();
    TrieNode(const TrieNode* parent);
    ~TrieNode();
    void AddChild(const char key, const TrieNode<T>* parent);
};

template<class T>
class Trie{
private:
    TrieNode<T> *root;

public:
    Trie();
    ~Trie();

    void Add(const char key[], T value);
    TrieNode<T>* FindNode(const char key[]);
    bool Search(const char key[], T &value);
    void Remove(const char key[]);
};

} // namespace trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR

#endif
