/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-11 19:27:41
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/trie_tree.cpp
 * @Description: 
 */

#include <iostream>
#include <cstring>
#include "AlgoLibR/data_structure/tree/trie_tree.h"
#include "AlgoLibR/data_structure/tree/kv_trie_tree.h"
#include "AlgoLibR/data_structure/tree/ac_trie.h"
#include "AlgoLibR/framework/register_types.h"
#include "AlgoLibR/ai/nlp/seg/ahocorasick_segment.h"

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace trie{

TrieNode::TrieNode(const wchar_t key) : key(key), parent(NULL){
}

TrieNode::TrieNode(const wchar_t key, TrieNode* parent) : key(key), parent(parent){
}

TrieNode::~TrieNode(){
    auto iter = this->child_nodes.begin();
    while(iter != this->child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }
    parent=NULL;
}

void TrieNode::AddChild(const wchar_t key){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new TrieNode(key, this);
}

void TrieNode::RemoveChild(const wchar_t key){
    auto iter = child_nodes.find(key);
    if( iter == child_nodes.end()){
        return;
    }
    delete iter->second;
    iter->second= NULL;
    child_nodes.erase(key);
}

template<typename NODETYPE>
Trie<NODETYPE>::Trie() : root(NULL), is_keys_added(false){
    root = new NODETYPE('/');
}

template<typename NODETYPE>
Trie<NODETYPE>::~Trie(){
    if(root != NULL){
        delete root;
        root = NULL;
    }
}    

template<typename NODETYPE>
NODETYPE* Trie<NODETYPE>::Add(const wchar_t keys[]){
    size_t key_len = wcslen(keys);
    if(key_len <= 0){
        return nullptr;
    }

    NODETYPE* p = root;
    for(size_t i = 0; i < key_len; i++){
        p->AddChild(keys[i]);
        p = p->child_nodes[keys[i]];
    }
    p->is_ending_key=true;

    is_keys_added=true;

    return p;
}

template<typename NODETYPE>
NODETYPE* Trie<NODETYPE>::FindNode(const wchar_t keys[]){
    size_t key_len = wcslen(keys);
    if(key_len <= 0){
        return NULL;
    }

    NODETYPE* p = root;
    for(size_t i = 0; i < key_len; i++){
        if(p->child_nodes.find(keys[i]) == p->child_nodes.end()){
            return NULL;
        }
        p = p->child_nodes[keys[i]];
    }

    return p;
}

template<typename NODETYPE>
bool Trie<NODETYPE>::Search(const wchar_t keys[]){

    NODETYPE* p = FindNode(keys);
    if(p && p->is_ending_key){
        return true;
    }
    return false;
}

template<typename NODETYPE>
void Trie<NODETYPE>::Remove(const wchar_t keys[]){
    NODETYPE* node = FindNode(keys);
    NODETYPE* parent;
    if(!node){
        return;
    }

    if(node->is_ending_key){
        node->is_ending_key=false;
    }
    while(node){
        if(node->child_nodes.size()==0 && !node->is_ending_key){
            parent = node->parent;
            parent->RemoveChild(node->key);
            node = parent;
        }else{
            break;
        }
    }
}

// register Trie
template class Trie<TrieNode>; 
template class Trie<ac_trie::ACTrieNode>;
template class Trie<AlgoLibR::ai::nlp::seg::ACSegNode>;

#define DEFINE_TRIE(T) \
    template class Trie<kv_trie::KVTrieNode<T>>; 
REGISTER_REAL_NUMBER_TYPES(DEFINE_TRIE)
REGISTER_wchar_t(DEFINE_TRIE)
REGISTER_wchar_t_ptr(DEFINE_TRIE) 

} // namespace trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR
