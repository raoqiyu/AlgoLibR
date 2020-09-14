/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-14 14:02:22
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/trie/ac_trie.cpp
 * @Description: Aho-Corasick ACTrie
 */

#include <map>
#include <queue>
#include <cstring>
#include "AlgoLibR/data_structure/trie/ac_trie.h"
#include "AlgoLibR/ai/nlp/seg/ahocorasick_segment.h"

#include <iostream>

namespace AlgoLibR{
namespace data_structure{
namespace trie{
namespace ac_trie{

ACTrieNode::ACTrieNode(const wchar_t key) : 
            key(key), parent(NULL), failure(NULL), is_ending_key(false){
}

ACTrieNode::ACTrieNode(const wchar_t key, ACTrieNode* parent) : 
            key(key), parent(parent), failure(NULL), is_ending_key(false){
}

ACTrieNode::~ACTrieNode(){
    auto iter = this->child_nodes.begin();
    while(iter != this->child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }
    parent=NULL;
    failure=NULL;
}

void ACTrieNode::AddChild(const wchar_t key){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new ACTrieNode(key, this);
}

void ACTrieNode::RemoveChild(const wchar_t key){
    auto iter = child_nodes.find(key);
    if( iter == child_nodes.end()){
        return;
    }
    delete iter->second;
    iter->second= NULL;
    child_nodes.erase(key);
}

template<typename NODETYPE>
void ACTrieBase<NODETYPE>::BuildFailurePtr(){
    if(!this->is_keys_added){
         return;
    }

    std::queue<NODETYPE*> nodes;
    // Step 1: set this->root's child nodes (node's depth is 1)
    for(auto iter = this->root->child_nodes.begin(); iter != this->root->child_nodes.end(); iter++){
        iter->second->failure = this->root;
        nodes.push(iter->second);
    }
    // Step 2: set other nodes (node's depth > 1)
    NODETYPE *current_node, *target_node, *failure_node;
    while(!nodes.empty()){
        current_node = nodes.front();
        nodes.pop();
        for(auto iter = current_node->child_nodes.begin(); iter != current_node->child_nodes.end(); iter++){
            target_node = iter->second;
            nodes.push(target_node);


            // find target_node's failure node from current_node's failure_node;
            failure_node = current_node->failure;
            while( failure_node && (failure_node->child_nodes.find(target_node->key) == failure_node->child_nodes.end()) ){
                failure_node = failure_node->failure;
            }
            if(!failure_node){
                target_node->failure = this->root;
            }else{
                target_node->failure = failure_node->child_nodes.find(target_node->key)->second;
            }
        }
    }
    this->is_keys_added = false;
}

template<typename NODETYPE>
std::wstring ACTrieBase<NODETYPE>::GetKeyFromNode(const NODETYPE *p){
    const NODETYPE *node  = p;
    std::wstring word;
    while(node != this->root){
        word.insert(0, 1, node->key);
        node = node->parent;
    }

    return word;
}

template<typename NODETYPE>
void ACTrieBase<NODETYPE>::CollectKeysFromNode(const NODETYPE *p, int pos, std::vector<std::pair<size_t,std::wstring>> &words){
    // check pointer is not NULL
    if(!p) return;

    NODETYPE *failure_node;
    std::wstring word;

    if(p->is_ending_key){
        word = GetKeyFromNode(p);
        if(!word.empty()){
            // std::cout << "current: " << pos << " " << word << std::endl;
            // if(!words.empty() && (pos+1-word.length() < words.back().first)) words.pop_back();            
            words.push_back(std::make_pair(pos,word));
            // return;
        } 
    }

    failure_node = p->failure;
    while( failure_node){
        if(failure_node->is_ending_key){
            word = GetKeyFromNode(failure_node);
            if(!word.empty()){
                // std::cout << "current: " << pos << " " << word << std::endl;
                // if(!words.empty() && (pos+1-word.length() < words.back().first)) words.pop_back();
                words.push_back(std::make_pair(pos,word));
                // return;
            }
        }
        failure_node = failure_node->failure;
    }
}

template<typename NODETYPE>
NODETYPE* ACTrieBase<NODETYPE>::GetNextNode(const NODETYPE *p, const wchar_t key){
    if(!p){
        return this->root;
    }

    auto iter = p->child_nodes.find(key);
    while(true){
        if(iter == p->child_nodes.end()){
            p = p->failure;
            if(p){
                iter = p->child_nodes.find(key);
            }else{
                return this->root;
            }
        }else{
            return iter->second;
        }
    }
}

template<typename NODETYPE>
std::vector<std::pair<size_t,std::wstring>> ACTrieBase<NODETYPE>::ParseText(const wchar_t keys[]){
    BuildFailurePtr();
    std::vector<std::pair<size_t,std::wstring>> words;
    size_t keys_len = wcslen(keys);
    if(keys_len == 0) return words;

    int i = 0;
    NODETYPE *p = GetNextNode(this->root, keys[0]);
    std::wstring word;

    for(i = 0; i < keys_len-1; i++){
        // Collect words ends with position i
        CollectKeysFromNode(p, i, words);

        p = GetNextNode(p, keys[i+1]);
    }

    // Collect words ends with position i
    CollectKeysFromNode(p, i, words);

    return words;
}

template class ACTrieBase<ACTrieNode>;
template class ACTrieBase<AlgoLibR::ai::nlp::seg::ACSegNode>;

} // namespace ac_trie
} // namespace trie
} // namespace data_struceture
} // namespace AlgoLibR