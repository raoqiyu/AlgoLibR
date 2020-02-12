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


TrieNode::TrieNode(){
    parent = NULL;
}

TrieNode::TrieNode(const TrieNode* parent){
    parent = parent;
}

TrieNode::~TrieNode(){
    auto iter = child_nodes.begin();
    while(iter != child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }

    delete parent;
}

void TrieNode::AddChild(const char key, const TrieNode* parent){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new TrieNode(parent);
}

Trie::Trie(){
    root = new TrieNode();
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
        p->AddChild(key[i], p);
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

} // namespace trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR
