/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-11 19:27:41
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/trie_tree.cpp
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
KVTrieNode<T>::KVTrieNode(){
    parent = NULL;
}

template<typename T>
KVTrieNode<T>::KVTrieNode(const KVTrieNode* parent){
    parent = parent;
}

template<typename T>
KVTrieNode<T>::~KVTrieNode(){
    auto iter = child_nodes.begin();
    while(iter != child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }

    delete parent;
}

template<typename T>
void KVTrieNode<T>::AddChild(const char key, const KVTrieNode<T>* parent){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new KVTrieNode<T>(parent);
}

template<typename T>
KVTrie<T>::KVTrie(){
    root = new KVTrieNode<T>();
}

template<typename T>
KVTrie<T>::~KVTrie(){
    delete root;
}

template<typename T>
void KVTrie<T>::Add(const char key[], const T value){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return ;
    }

    KVTrieNode<T>* p = root;
    for(size_t i = 0; i < key_len; i++){
        p->AddChild(key[i], p);
        p = p->child_nodes[key[i]];
    }
    p->value = value;
    p->is_ending_char=true;
}

template<typename T>
KVTrieNode<T>* KVTrie<T>::FindNode(const char key[]){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return NULL;
    }

    KVTrieNode<T>* p = root;
    for(size_t i = 0; i < key_len; i++){
        if(p->child_nodes.find(key[i]) == p->child_nodes.end()){
            return NULL;
        }
        p = p->child_nodes[key[i]];
    }

    return p;
}

template<typename T>
bool KVTrie<T>::Search(const char key[], T &value){

    KVTrieNode<T>* p = FindNode(key);
    if(p && p->is_ending_char){
        value = p->value;
        return true;
    }

    return false;
}

template<typename T>
void KVTrie<T>::Remove(const char key[]){
    KVTrieNode<T>* node = FindNode(key);
    KVTrieNode<T>* parent;
    if(node && node->is_ending_char){
        node->is_ending_char=false;
    }

    while(node){
        if(node->child_nodes.size()==0){
            parent = node->parent;
            delete node;
        }else{
            break;
        }
    }
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
