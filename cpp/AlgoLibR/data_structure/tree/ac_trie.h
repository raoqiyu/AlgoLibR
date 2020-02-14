/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-14 13:42:26
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/ac_trie_tree.h
 * @Description: Aho-Corasick Trie
 */

#ifndef DS_TREE_ACTRIE_H
#define DS_TREE_ACTRIE_H

#include <string>
#include <vector>

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace ac_trie{

class ACTrieNode{
public:
    char key;
    bool is_ending_char;
    ACTrieNode *parent=NULL;
    ACTrieNode *failure=NULL;
    std::map<char, ACTrieNode*> child_nodes;

    ~ACTrieNode();
    ACTrieNode(const char key);
    ACTrieNode(const char key, ACTrieNode* parent);
    void AddChild(const char key);
    void RemoveChild(const char key);

};

class ACTrie{
private:
    ACTrieNode *root;
    bool is_failure_built=false;

public:
    ACTrie();
    ~ACTrie();
    
    void Add(const char key[]);
    ACTrieNode* FindNode(const char key[]);
    bool Search(const char key[]);
    void Remove(const char key[]);

    void BuildFailurePtr();
    std::string GetKeyFromNode(const ACTrieNode *p);
    ACTrieNode* GetNextNode(const ACTrieNode *p, const char key);
    std::vector<std::pair<int,std::string>> ParseText(const char keys[]);

};


} // namespace ac_trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR

#endif
