/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-14 13:42:26
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/ac_trie_tree.h
 * @Description: Aho-Corasick Trie
 */

#ifndef DS_TREE_ACTRIE_H
#define DS_TREE_ACTRIE_H

#include <string>
#include <stdlib.h>
#include <vector>
#include "AlgoLibR/data_structure/tree/trie_tree.h"

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace ac_trie{

class ACTrieNode{
public:
    char key;
    bool is_ending_key;
    ACTrieNode *parent=NULL;
    ACTrieNode *failure=NULL;
    std::map<char, ACTrieNode*> child_nodes;

    ~ACTrieNode();
    ACTrieNode(const char key);
    ACTrieNode(const char key, ACTrieNode* parent);
    void AddChild(const char key);
    void RemoveChild(const char key);

};

template<typename NODETYPE>
class ACTrieBase : public trie::Trie<NODETYPE>{
public:
    std::vector<std::pair<size_t,std::string>> ParseText(const char keys[]);

protected:
    void BuildFailurePtr();
    NODETYPE* FindNode(const char key[]);
    NODETYPE* GetNextNode(const NODETYPE *p, const char key);

private:
    std::string GetKeyFromNode(const NODETYPE *p);
    void CollectKeysFromNode(const NODETYPE *p, int pos, std::vector<std::pair<size_t,std::string>> &words);
};

class ACTrie : public ACTrieBase<ACTrieNode>{

};

} // namespace ac_trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR

#endif
