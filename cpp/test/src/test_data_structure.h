/*
Author: raoqiyu@gmail.com
Date: 2020-02-07 17:07:11
FilePath: /AlgoLibR/cpp/test/AlgoLibR/test_data_structure.h
Description: 
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "AlgoLibR/data_structure/heap.h"
#include "AlgoLibR/data_structure/tree/trie_tree.h"
#include "AlgoLibR/data_structure/tree/kv_trie_tree.h"
#include "AlgoLibR/data_structure/tree/ac_trie.h"

void test_heap(){
    printf("Test Heap\n");

    AlgoLibR::data_structure::heap::HeapImp<int> heap(5, true);

    heap.insert(2);
    heap.insert(100);
    heap.insert(1);
    heap.insert(45);
    heap.insert(6);

    printf("Current max: %d\n", heap.get());
    heap.remove();
    printf("Current max: %d\n", heap.get());
    heap.remove();
    printf("Current max: %d\n", heap.get());
    heap.remove();
    printf("Current max: %d\n", heap.get());
    heap.remove();
    printf("Current max: %d\n", heap.get());
    heap.remove();
    printf("\n");
}


void test_Trie(){
    std::cout << "Test Trie" << std::endl;

    AlgoLibR::data_structure::tree::trie::Trie str_trie;


    str_trie.Add("hello");
    str_trie.Add("world");

    std::cout << "Searching" << std::endl; 

    if(!str_trie.Search("hello")){
        std::cout << "Wrong! : hello" << std::endl;
    }

    if(!str_trie.Search("world")){
        std::cout << "Wrong!: world" << std::endl;
    }
    
    if(str_trie.Search("he")){
        std::cout << "Wrong! : he" << std::endl;
    }

    if(str_trie.Search("wor")){
        std::cout << "Wrong! : wor" << std::endl;
    }

    if(str_trie.Search("word")){
        std::cout << "Wrong! : word" << std::endl;
    }

    std::cout << "Searching Stage 2" << std::endl; 
    str_trie.Add("hi");
    str_trie.Add("hi");
    if(!str_trie.Search("hi")){
        std::cout << "Wrong!   hi should exist" << std::endl;
    }

    str_trie.Add("hi LiSi");
    if(!str_trie.Search("hi")){
        std::cout << "Wrong!   hi should exist" << std::endl;
    }

    str_trie.Remove("hi");
    if(str_trie.Search("hi")){
        std::cout << "Wrong!   hi should not exist" << std::endl;
    }
    
    str_trie.Remove("hi");
    if(str_trie.Search("hi")){
        std::cout << "Wrong!   hi should not exist" << std::endl;
    }

    if(!str_trie.Search("hi LiSi")){
        std::cout << "Wrong!   hi LiSi should exist" << std::endl;
    }

    std::cout << "Searching Stage 3" << std::endl; 

    str_trie.Add("hit");
    if(!str_trie.Search("hit")){
        std::cout << "Wrong!   hit should exist" << std::endl;
    }
    std::cout << "Remove" << std::endl; 
    str_trie.Remove("hit");
    // if(str_trie.Search("hit")){
        // std::cout << "Wrong!   hi LiSi should exist" << std::endl;
    // }

    std::cout << "End\n" << std::endl;
}

void test_KVTrie(){
    std::cout << "Test KVTrie" << std::endl <<     std::flush;
    AlgoLibR::data_structure::tree::kv_trie::KVTrie<char*> str_trie;

    bool is_in;
    char* ret;

    str_trie.Add("hello", "world");
    str_trie.Add("world", "!");

    if(!str_trie.Search("hello", ret)){
        std::cout << "Wrong!" << std::endl;
    }

    if(!str_trie.Search("world", ret)){
        std::cout << "Wrong!" << std::endl;
    }
    
    if(str_trie.Search("he", ret)){
        std::cout << "Wrong!" << std::endl;
    }

    if(str_trie.Search("wor", ret)){
        std::cout << "Wrong!" << std::endl;
    }

    if(str_trie.Search("word", ret)){
        std::cout << "Wrong!" << std::endl;
    }


    str_trie.Add("hi", "this is a test");
    str_trie.Search("hi", ret);
    std::cout << "hi : " << ret << std::endl;

    str_trie.Add("hi", " Done");
    str_trie.Search("hi", ret);
    std::cout << "hi : " << ret << std::endl;
    if(!str_trie.Search("hi", ret)){
        std::cout << "Wrong!   hi should exist" << std::endl;
    }

    str_trie.Add("hi LiSi", "How are you?");
    if(!str_trie.Search("hi", ret)){
        std::cout << "Wrong!   hi should exist" << std::endl;
    }
    str_trie.Remove("hi");
    is_in = str_trie.Search("hi", ret);
    std::cout << "hi : " << ret << std::endl;
    if(is_in){
        std::cout << "Wrong!   hi should not exist" << std::endl;
    }
    
    str_trie.Remove("hi");
    is_in = str_trie.Search("hi", ret);
    std::cout << "hi : " << ret << std::endl;
    if(is_in){
        std::cout << "Wrong!   hi should not exist" << std::endl;
    }

    is_in = str_trie.Search("hi LiSi", ret);
    std::cout << "hi LiSi : " << ret << std::endl;
    if(!is_in){
        std::cout << "Wrong!   hi LiSi should exist" << std::endl;
    }

    str_trie.Add("hit", "Begin");
    is_in = str_trie.Search("hit", ret);
    if(!is_in){
        std::cout << "Wrong!   hit should exist" << std::endl;
    }
    std::cout << "Remove" << std::endl; 
    str_trie.Remove("hit");
    // if(str_trie.Search("hit")){
        // std::cout << "Wrong!   hi LiSi should exist" << std::endl;
    // }

    std::cout << "End\n" << std::endl;
}

void test_ACTrie(){
    std::cout << "Test AC Trie" << std::endl;
    AlgoLibR::data_structure::tree::ac_trie::ACTrie ac_trie;

    bool is_in;
    std::cout << "Add word" << std::endl;
    ac_trie.Add("hers");
    ac_trie.Add("his");
    ac_trie.Add("she");
    ac_trie.Add("he");
    ac_trie.Add("sh");
    ac_trie.Add("s");
    ac_trie.Add("h");
    ac_trie.Add("hr");


    std::cout << "Searching" << std::endl;
    is_in = ac_trie.Search("his");
    if(!is_in){
        std::cout << "Wrong!   his should exist" << std::endl; 
    }

    is_in = ac_trie.Search("she");
    if(!is_in){
        std::cout << "Wrong!   she should exist" << std::endl; 
    }

    std::cout << "Searching" << std::endl;
    is_in = ac_trie.Search("shi");
    if(is_in){
        std::cout << "Wrong!   hi should not exist" << std::endl; 
    }

    std::cout << "Parsing" << std::endl;
    std::vector<std::pair<int,std::string>> parsed = ac_trie.ParseText("ushers");
    std::cout << "output" << std::endl;
    for(auto i = 0; i < parsed.size(); i++){
        std::cout << parsed[i].first << ":" << parsed[i].second << ", " ;
    }
    std::cout << std::endl;

    ac_trie.Add("算法");
    ac_trie.Add("描述");
    ac_trie.Add("问题");
    ac_trie.Add("策略");
    ac_trie.Add("方案");
    ac_trie.Add("描述");
    parsed = ac_trie.ParseText("算法（Algorithm）是指解题方案的准确而完整的描述，是一系列解决问题的清晰指令，算法代表着用系统的方法描述解决问题的策略机制。");
    for(auto i = 0; i < parsed.size(); i++){
        std::cout << parsed[i].first << ":" << parsed[i].second << ", " ;
    }
    std::cout << std::endl;
}


void test_ds(){
    test_heap();
    test_Trie();
    test_KVTrie();
    test_ACTrie();
}