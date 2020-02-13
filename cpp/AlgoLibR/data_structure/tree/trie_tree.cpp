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


TrieNode::TrieNode(const char key){
    this->key = key;
    parent = NULL;
}

TrieNode::TrieNode(const char key, TrieNode* parent){
    this->key = key;
    this->parent = parent;
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

void TrieNode::AddChild(const char key){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new TrieNode(key, this);
}

void TrieNode::RemoveChild(const char key){
    auto iter = child_nodes.find(key);
    if( iter == child_nodes.end()){
        return;
    }
    delete iter->second;
    iter->second= NULL;
    child_nodes.erase(key);
}

Trie::Trie(){
    root = new TrieNode('/');
}

Trie::~Trie(){
    delete root;
}

void Trie::Add(const char key[]){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return ;
    }

    TrieNode* p = root;
    for(size_t i = 0; i < key_len; i++){
        p->AddChild(key[i]);
        p = p->child_nodes[key[i]];
    }
    p->is_ending_char=true;
}

TrieNode* Trie::FindNode(const char key[]){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return NULL;
    }

    TrieNode* p = root;
    for(size_t i = 0; i < key_len; i++){
        if(p->child_nodes.find(key[i]) == p->child_nodes.end()){
            return NULL;
        }
        p = p->child_nodes[key[i]];
    }

    return p;
}

bool Trie::Search(const char key[]){

    TrieNode* p = FindNode(key);
    if(p && p->is_ending_char){
        return true;
    }
    return false;
}

void Trie::Remove(const char key[]){
    TrieNode* node = FindNode(key);
    TrieNode* parent;
    if(!node){
        return;
    }

    if(node->is_ending_char){
        node->is_ending_char=false;
    }
    while(node){
        if(node->child_nodes.size()==0){
            parent = node->parent;
            parent->RemoveChild(node->key);
            node = parent;
        }else{
            break;
        }
    }
}

} // namespace trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR
