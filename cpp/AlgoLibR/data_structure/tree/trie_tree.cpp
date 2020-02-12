/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-11 19:27:41
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/trie_tree.cpp
 * @Description: 
 */

#include <iostream>
#include <cstring>
#include "AlgoLibR/data_structure/tree/trie_tree.h"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace trie{


template<typename T>
TrieNode<T>::TrieNode(){
    parent = NULL;
}

template<typename T>
TrieNode<T>::TrieNode(const TrieNode* parent){
    parent = parent;
}

template<typename T>
TrieNode<T>::~TrieNode(){
    auto iter = child_nodes.begin();
    while(iter != child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }

    delete parent;
}

template<typename T>
void TrieNode<T>::AddChild(const char key, const TrieNode<T>* parent){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new TrieNode<T>(parent);
}

template<typename T>
Trie<T>::Trie(){
    root = new TrieNode<T>();
}

template<typename T>
Trie<T>::~Trie(){
    delete root;
}

template<typename T>
void Trie<T>::Add(const char key[], T value){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return ;
    }

    TrieNode<T>* p = root;
    for(size_t i = 0; i < key_len; i++){
        p->AddChild(key[i], p);
        p = p->child_nodes[key[i]];
    }
    p->value = value;
    p->is_ending_char=true;
}

template<typename T>
TrieNode<T>* Trie<T>::FindNode(const char key[]){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return NULL;
    }

    TrieNode<T>* p = root;
    for(size_t i = 0; i < key_len; i++){
        if(p->child_nodes.find(key[i]) == p->child_nodes.end()){
            return NULL;
        }
        p = p->child_nodes[key[i]];
    }

    return p;
}

template<typename T>
bool Trie<T>::Search(const char key[], T &value){

    TrieNode<T>* p = FindNode(key);
    if(p && p->is_ending_char){
        value = p->value;
        return true;
    }

    return false;
}

template<typename T>
void Trie<T>::Remove(const char key[]){
    TrieNode<T>* node = FindNode(key);
    TrieNode<T>* parent;
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
    template class TrieNode<T>; \
    template class Trie<T>; 
REGISTER_REAL_NUMBER_TYPES(DEFINE_TRIE)

}
}
}
}
