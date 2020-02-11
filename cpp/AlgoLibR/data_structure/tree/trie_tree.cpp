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
    cnt = 0;
}

template<typename T>
void TrieNode<T>::AddChild(char key){
    if(child_nodes.find(key) != child_nodes.end()){
        child_nodes[key]->cnt++;
        return;
    }
    child_nodes[key] = new TrieNode<T>();
}

// void TrieNode::RemoveChild(char key){
//     TrieNode child = new TrieNode(value);
//     child_nodes[key] = child;
// }


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
        p->AddChild(key[i]);
        p = p->child_nodes[key[i]];
    }
    p->value = value;
    p->is_ending_char=true;
}

template<typename T>
bool Trie<T>::Search(const char key[]){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return false;
    }

    TrieNode<T>* p = root;
    for(size_t i = 0; i < key_len; i++){
        if(p->child_nodes.find(key[i]) == p->child_nodes.end()){
            return false;
        }

        p = p->child_nodes[key[i]];
    }
    if(p && p->is_ending_char){
        return true;
    }

    return false;
}


#define DEFINE_TRIE(T) \
    template class TrieNode<T>; \
    template class Trie<T>; 
REGISTER_REAL_NUMBER_TYPES(DEFINE_TRIE)
}
}
}
}
