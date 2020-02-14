/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-14 14:02:22
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/data_structure/tree/ac_trie.cpp
 * @Description: Aho-Corasick ACTrie
 */

#include <map>
#include <queue>
#include <cstring>
#include "AlgoLibR/data_structure/tree/ac_trie.h"

#include <iostream>

namespace AlgoLibR{
namespace data_structure{
namespace tree{
namespace ac_trie{

ACTrieNode::ACTrieNode(const char key){
    this->key =key;
    parent = NULL;
    failure = NULL;
    is_ending_char=false;
}

ACTrieNode::ACTrieNode(const char key, ACTrieNode* parent){
    this->key = key;
    this->parent = parent;
    failure=NULL;
    is_ending_char=false;
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

void ACTrieNode::AddChild(const char key){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new ACTrieNode(key, this);
}

void ACTrieNode::RemoveChild(const char key){
    auto iter = child_nodes.find(key);
    if( iter == child_nodes.end()){
        return;
    }
    delete iter->second;
    iter->second= NULL;
    child_nodes.erase(key);
}



ACTrie::ACTrie(){
    root = new ACTrieNode('/');
}

ACTrie::~ACTrie(){
    delete root;
}

void ACTrie::Add(const char key[]){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return ;
    }

    ACTrieNode* p = root;
    for(size_t i = 0; i < key_len; i++){
        p->AddChild(key[i]);
        p = p->child_nodes[key[i]];
    }
    p->is_ending_char=true;
}

ACTrieNode* ACTrie::FindNode(const char key[]){
    size_t key_len = strlen(key);
    if(key_len <= 0){
        return NULL;
    }

    ACTrieNode* p = root;
    for(size_t i = 0; i < key_len; i++){
        if(p->child_nodes.find(key[i]) == p->child_nodes.end()){
            return NULL;
        }
        p = p->child_nodes[key[i]];
    }

    return p;
}

bool ACTrie::Search(const char key[]){

    ACTrieNode* p = FindNode(key);
    if(p && p->is_ending_char){
        return true;
    }
    return false;
}

void ACTrie::Remove(const char key[]){
    ACTrieNode* node = FindNode(key);
    ACTrieNode* parent;
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


void ACTrie::BuildFailurePtr(){
    if(is_failure_built){
         return;
    }

    std::queue<ACTrieNode*> nodes;
    // Step 1: set root's child nodes (node's depth is 1)
    for(auto iter = root->child_nodes.begin(); iter != root->child_nodes.end(); iter++){
        iter->second->failure = root;
        nodes.push(iter->second);
    }
    // Step 2: set other nodes (node's depth > 1)
    ACTrieNode *current_node, *target_node, *failure_node;
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
                target_node->failure = root;
            }else{
                target_node->failure = failure_node->child_nodes.find(target_node->key)->second;
            }
        }
    }

    is_failure_built = true;
}

std::string ACTrie::GetKeyFromNode(const ACTrieNode *p){
    const ACTrieNode *node  = p;
    std::string word;
    while(node != root){
        word.insert(0, 1, node->key);
        node = node->parent;
    }

    return word;
}

void ACTrie::CollectKeysFromNode(const ACTrieNode *p, int pos, std::vector<std::pair<int,std::string>> &words){
    // check pointer is not NULL
    if(!p) return;

    ACTrieNode *failure_node;
    std::string word;

    if(p->is_ending_char){
        word = GetKeyFromNode(p);
        if(!word.empty()){
            // std::cout << "p->is_ending: " << word << std::endl << std::flush;
            words.push_back(std::make_pair(pos,word));
        } 
    }

    failure_node = p->failure;
    while( failure_node){
        if(failure_node->is_ending_char){
            word = GetKeyFromNode(failure_node);
            if(!word.empty()){
                // std::cout << "failure->key:  " << failure_node->key << std::endl << std::flush;
                // std::cout << "failure->is_ending: " << word << std::endl << std::flush;
                words.push_back(std::make_pair(pos,word));
            }
        }
        failure_node = failure_node->failure;
    }
}


ACTrieNode* ACTrie::GetNextNode(const ACTrieNode *p, const char key){
    ACTrieNode *next;
    if(!p){
        return root;
    }

    auto iter = p->child_nodes.find(key);
    while(iter == p->child_nodes.end()){
        p = p->failure;
        if(p){
            iter = p->child_nodes.find(key);
        }else{
            break;
        }
    }

    if(p){
        next = iter->second;
    }else{
        next = root;
    }
    return next;
}

std::vector<std::pair<int,std::string>> ACTrie::ParseText(const char keys[]){
    BuildFailurePtr();

    size_t keys_len = strlen(keys);
    int i = 0;
    ACTrieNode *p = root, *failure_node;
    std::vector<std::pair<int,std::string>> words;
    std::string word;

    for(i = 0; i < keys_len; i++){
        // Collect words ends with position i
        CollectKeysFromNode(p, i, words);

        p = GetNextNode(p, keys[i]);
    }

    // Collect words ends with position i
    CollectKeysFromNode(p, i, words);

    return words;
}

} // namespace ac_trie
} // namespace tree
} // namespace data_struceture
} // namespace AlgoLibR