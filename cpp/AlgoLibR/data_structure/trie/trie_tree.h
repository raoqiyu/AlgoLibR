/*
Author: raoqiyu@gmail.com
Date: 2020-02-11 18:34:27
FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/trie/trie_tree.h
Description: 
 */

#ifndef DS_TREE_TRIE_H
#define DS_TREE_TRIE_H

#include <map>
#include <stdlib.h>

namespace AlgoLibR{
namespace data_structure{
namespace trie{
namespace trie{

class TrieNode{
public:
    wchar_t key;
    bool is_ending_key;
    std::map<wchar_t, TrieNode*> child_nodes;
    TrieNode *parent;

    TrieNode(const wchar_t key);
    TrieNode(const wchar_t key, TrieNode* parent);
    ~TrieNode();
    void AddChild(const wchar_t key);
    void RemoveChild(const wchar_t key);
};


template<typename NODETYPE>
class Trie{
protected:
    NODETYPE* root;
    bool is_keys_added;

public:
    Trie();
    ~Trie();

    NODETYPE* Add(const wchar_t keys[]);
    NODETYPE* FindNode(const wchar_t keys[]);
    bool Search(const wchar_t keys[]);
    void Remove(const wchar_t keys[]);
};

} // namespace trie
} // namespace trie
} // namespace data_struceture
} // namespace AlgoLibR

#endif
