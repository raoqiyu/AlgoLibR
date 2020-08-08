/*
 * @Autor: raoqiyu@gmail.com
 * @Date: 2020-08-07 20:05:43
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/ai/nlp/mining/word/ngram_counter.cpp
 * @Description: 
 */

#include <fstream>
#include <iostream>
#include <queue>
#include "AlgoLibR/ai/nlp/mining/word/ngram_counter.h"

namespace AlgoLibR{
namespace ai{
namespace nlp{
namespace mining{
namespace word{


Node::Node(const wchar_t key) : key(key), parent(NULL), is_ending_key(false){
}

Node::Node(const wchar_t key, Node* parent) : key(key), parent(parent), is_ending_key(false){
}

Node::~Node(){
    auto iter = this->child_nodes.begin();
    while(iter != this->child_nodes.end()){
        delete iter->second;
        iter->second = NULL;
        child_nodes.erase(iter++);
    }
    parent=NULL;
}

void Node::AddChild(const wchar_t key){
    if(child_nodes.find(key) != child_nodes.end()){
        return;
    }
    child_nodes[key] = new Node(key, this);
}

void Node::RemoveChild(const wchar_t key){
    auto iter = child_nodes.find(key);
    if( iter == child_nodes.end()){
        return;
    }
    delete iter->second;
    iter->second= NULL;
    child_nodes.erase(key);
}



NGramCounter::NGramCounter(const char *src_fname, const char *dst_fname, 
                            const unsigned int top_n, const wchar_t *delimiters) : src_file(src_fname), dst_file(dst_fname), top_n(top_n){
    auto n_delim = std::wcslen(delimiters);
    for(auto i = 0; i < n_delim; i++){
        this->delimiters.insert(delimiters[i]);
    }
    if (!src_file.is_open()){
        std::wcout << src_fname << L" 文件打开失败..." << std::endl;
        return;
    }
    if (!dst_file.is_open()){
        std::wcout << dst_fname << L" 文件打开失败..." << std::endl;
        return;
    }
    return;
}


void NGramCounter::AddNGram(const wchar_t gram[]){
    size_t gram_len = wcslen(gram);
    if(gram_len <= 0){
        return ;
    }

    Node* p = this->root;
    for(size_t i = 0; i < gram_len; i++){
        p->AddChild(gram[i]);
        p = p->child_nodes[gram[i]];
    }
    p->value += 1;
    p->is_ending_key=true;
}


std::vector<std::wstring> NGramCounter::ParseLine(const std::wstring &line){
    std::vector<std::wstring> grams;
    std::wstring gram;
    for(auto c:line){
        if(delimiters.find(c) != delimiters.end()){
            for(auto i = 2; i < gram.size(); i++){
                grams.emplace_back(gram.substr(0,i));
            }
            gram.clear();
            continue;
        }else if(gram.size() == top_n){
            for(auto i = 2; i <= gram.size(); i++){
                grams.emplace_back(gram.substr(0,i));
            }
            gram = gram.substr(1,gram.size()-1);
        }
        gram.push_back(c);
    }
    return grams;
}


void NGramCounter::ExportGrams(Node *node, std::wstring gram){    
    /*DFS
    */
    if(node == nullptr){
        return;
    }

    if(node->is_ending_key){
        dst_file << gram << ' ' << node->value << '\n';
    }

    for(auto iter: node->child_nodes){
        gram.push_back(iter.first);
        ExportGrams(iter.second, gram);
        gram.pop_back();
    }
}


void NGramCounter::Count(){
    
    std::wstring line;
    while(std::getline(src_file,line)){
        for(auto gram : ParseLine(line)){
            AddNGram(gram.c_str());
        }
    }

    std::wstring gram;
    ExportGrams(root, gram);
    
    src_file.close();
    dst_file.close();
}


} // namespace word
} // namespace mining
} // namespace nlp
} // namespace ai
} // namespace AlgoLibR