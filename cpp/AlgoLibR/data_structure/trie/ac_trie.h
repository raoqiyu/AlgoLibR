/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-14 13:42:26
FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/trie/ac_trie.h
 * @Description: Aho-Corasick Trie
 */

#ifndef DS_TREE_ACTRIE_H
#define DS_TREE_ACTRIE_H

#include <string>
#include <stdlib.h>
#include <vector>
#include "AlgoLibR/data_structure/trie/trie_tree.h"

namespace AlgoLibR{
namespace data_structure{
namespace trie{
namespace ac_trie{

class ACTrieNode{
public:
    wchar_t key;
    bool is_ending_key;
    ACTrieNode *parent=NULL;
    ACTrieNode *failure=NULL;
    std::map<wchar_t, ACTrieNode*> child_nodes;

    ~ACTrieNode();
    ACTrieNode(const wchar_t key);
    ACTrieNode(const wchar_t key, ACTrieNode* parent);
    void AddChild(const wchar_t key);
    void RemoveChild(const wchar_t key);

};

template<typename NODETYPE>
class ACTrieBase : public trie::Trie<NODETYPE>{
public:
    std::vector<std::pair<size_t,std::wstring>> ParseText(const wchar_t keys[]);

protected:
    void BuildFailurePtr();
    NODETYPE* FindNode(const wchar_t key[]);
    NODETYPE* GetNextNode(const NODETYPE *p, const wchar_t key);

private:
    std::wstring GetKeyFromNode(const NODETYPE *p);
    void CollectKeysFromNode(const NODETYPE *p, int pos, std::vector<std::pair<size_t,std::wstring>> &words);
};

class ACTrie : public ACTrieBase<ACTrieNode>{

};

} // namespace ac_trie
} // namespace trie
} // namespace data_struceture
} // namespace AlgoLibR

#endif
