/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-11 19:27:41
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/kv_trie_tree.cpp
 * @Description: 
 */

#include <iostream>
#include <cstring>
#include "AlgoLibR/data_structure/tree/kv_trie_tree.h"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace kv_trie{


template<typename T>
KVTrieNode<T>::KVTrieNode(const char key){
    this->key = key;
    parent = NULL;
}

template<typename T>
KVTrieNode<T>::KVTrieNode(const char key, KVTrieNode* parent){
    this->key = key;
    this->parent = parent;
}

template<typename T>
KVTrieNode<T>::~KVTrieNode(){
    auto iter = child_nodes.begin();
    while(iter != child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }

    parent = NULL;
}

template<typename T>
void KVTrieNode<T>::AddChild(const char key){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new KVTrieNode<T>(key, this);
}

template<typename T>
void KVTrieNode<T>::RemoveChild(const char key){
    auto iter = child_nodes.find(key);
    if( iter == child_nodes.end()){
        return;
    }
    delete iter->second;
    iter->second= NULL;
    child_nodes.erase(key);
}

template<typename T>
void KVTrie<T>::Add(const char key[], const T value){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return ;
    }

    KVTrieNode<T>* p = this->root;
    for(size_t i = 0; i < key_len; i++){
        p->AddChild(key[i]);
        p = p->child_nodes[key[i]];
    }
    p->value = value;
    p->is_ending_key=true;
}

template<typename T>
bool KVTrie<T>::Search(const char key[], T &value){

    KVTrieNode<T>* p = this->FindNode(key);
    if(p && p->is_ending_key){
        value = p->value;
        return true;
    }

    return false;
}


#define DEFINE_TRIE(T) \
    template class KVTrieNode<T>; \
    template class KVTrie<T>; 
REGISTER_REAL_NUMBER_TYPES(DEFINE_TRIE)
REGISTER_char(DEFINE_TRIE)
REGISTER_charptr(DEFINE_TRIE) 


} // namespace kv_trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR
