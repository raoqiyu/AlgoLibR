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
#include "AlgoLibR/data_structure/tree/trie_tree.h"

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

class ACTrie : public trie::Trie<ACTrieNode>{
private:
    bool is_failure_built=false;

public:
    std::vector<std::pair<int,std::string>> ParseText(const char keys[]);

private:
    void BuildFailurePtr();
    ACTrieNode* FindNode(const char key[]);
    std::string GetKeyFromNode(const ACTrieNode *p);
    void CollectKeysFromNode(const ACTrieNode *p, int pos, std::vector<std::pair<int,std::string>> &words);
    ACTrieNode* GetNextNode(const ACTrieNode *p, const char key);
};

} // namespace ac_trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR

#endif
