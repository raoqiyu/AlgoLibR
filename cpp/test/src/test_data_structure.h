/*
Author: raoqiyu@gmail.com
Date: 2020-02-07 17:07:11
FilePath: /AlgoLibR/cpp/test/src/test_data_structure.h
Description: 
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "AlgoLibR/data_structure/heap.hpp"
#include "AlgoLibR/data_structure/tree/trie_tree.h"
#include "AlgoLibR/data_structure/tree/kv_trie_tree.h"
#include "AlgoLibR/data_structure/tree/ac_trie.h"

bool test_max(std::pair<int,int> x, std::pair<int,int> y){
    return x.second > y.second;
}


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

    int arr[5]  = {2, 100, 1 ,45, 6};
    int * result, k=2;

    result = AlgoLibR::data_structure::heap::klargest(arr, 5, k);
    for(auto i = 0; i < k; i++){
        std::wcout << result[i] << " ";
    }
    std::wcout << std::endl;
    delete result;
    
    result = AlgoLibR::data_structure::heap::ksmallest(arr, 5, k);
    for(auto i = 0; i < k; i++){
        std::wcout << result[i] << " ";
    }
    std::wcout << std::endl;
    delete result;

    // std::vector<std::pair<int,int>> test_arr, result2;
    // test_arr.push_back(std::make_pair(1,4));
    // test_arr.push_back(std::make_pair(2,3));
    // test_arr.push_back(std::make_pair(3,2));
    // test_arr.push_back(std::make_pair(4,1));

    // result2 = AlgoLibR::data_structure::heap::klargestKey<std::vector<std::pair<int,int>>,
    //                                                    std::pair<int,int>>(test_arr, 4, 1, test_max);
    // for(auto i = 0; i < k; i++){
    //     std::wcout << result2[i].first << ',' << result2[i].second << " ";
    // }
    // std::wcout << std::endl;


    printf("\n\n");
}


void test_Trie(){
    std::wcout << "Test Trie" << std::endl;

    AlgoLibR::data_structure::tree::trie::Trie<AlgoLibR::data_structure::tree::trie::TrieNode> str_trie;


    str_trie.Add(L"hello");
    str_trie.Add(L"world");
    str_trie.Add(L"我");

    std::wcout << "Searching" << std::endl; 

    if(!str_trie.Search(L"hello")){
        std::wcout << "Wrong! : hello" << std::endl;
    }

    if(!str_trie.Search(L"world")){
        std::wcout << "Wrong!: world" << std::endl;
    }
    
    if(str_trie.Search(L"he")){
        std::wcout << "Wrong! : he" << std::endl;
    }

    if(str_trie.Search(L"wor")){
        std::wcout << "Wrong! : wor" << std::endl;
    }

    if(str_trie.Search(L"我")){
        std::wcout << "Wrong! : word" << std::endl;
    }

    std::wcout << "Searching Stage 2" << std::endl; 
    str_trie.Add(L"his");
    str_trie.Add(L"hi");
    if(!str_trie.Search(L"hi")){
        std::wcout << "Wrong!   hi should exist" << std::endl;
    }
    
    str_trie.Remove(L"his");
    if(!str_trie.Search(L"hi")){
        std::wcout << "Wrong!   hi should exist" << std::endl;
    }

    str_trie.Add(L"我们");
    if(!str_trie.Search(L"我")){
        std::wcout << "Wrong!   hi should exist" << std::endl;
    }

    str_trie.Remove(L"我");
    if(str_trie.Search(L"我")){
        std::wcout << L"Wrong!   我 should not exist" << std::endl;
    }

     str_trie.Remove(L"我");
    if(str_trie.Search(L"我")){
        std::wcout << L"Wrong!   我 should not exist" << std::endl;
    }
   
    if(!str_trie.Search(L"我们")){
        std::wcout << L"Wrong!   我们 should exist" << std::endl;
    }

    std::wcout << "Searching Stage 3" << std::endl; 

    std::wcout << "End\n" << std::endl;
}

void test_KVTrie(){
    std::wcout << "Test KVTrie" << std::endl <<     std::flush;
    AlgoLibR::data_structure::tree::kv_trie::KVTrie<wchar_t*> str_trie;

    bool is_in;
    wchar_t* ret;

    str_trie.Add(L"hello", L"嗨");
    str_trie.Add(L"world", L"世界");

    if(!str_trie.Search(L"hello", ret)){
        std::wcout << "Wrong!" << std::endl;
    }

    if(!str_trie.Search(L"world", ret)){
        std::wcout << "Wrong!" << std::endl;
    }
    
    if(str_trie.Search(L"he", ret)){
        std::wcout << "Wrong!" << std::endl;
    }

    if(str_trie.Search(L"wor", ret)){
        std::wcout << "Wrong!" << std::endl;
    }

    if(str_trie.Search(L"word", ret)){
        std::wcout << "Wrong!" << std::endl;
    }


    str_trie.Add(L"Test", L"测试ing");
    str_trie.Search(L"Test", ret);
    std::wcout << L"Test : " << ret << std::endl;

    str_trie.Add(L"Test", L"测试结束");
    str_trie.Search(L"Test", ret);
    std::wcout << "Test : " << ret << std::endl;

    str_trie.Add(L"Test twice", L"I'm back");

    str_trie.Remove(L"Test");
    is_in = str_trie.Search(L"Test", ret);
    if(is_in){
        std::wcout << "Wrong! Test should not exist" << std::endl;
    }
    
    is_in = str_trie.Search(L"Test twice", ret);
    std::wcout << L"Test twice : " << ret << std::endl;
    if(!is_in){
        std::wcout << "Wrong! Test twice should exist" << std::endl;
    }

    std::wcout << "End\n" << std::endl;
}

void test_ACTrie(){
    std::wcout << "Test AC Trie" << std::endl;
    AlgoLibR::data_structure::tree::ac_trie::ACTrie ac_trie;

    bool is_in;
    std::wcout << "Add word" << std::endl;
    ac_trie.Add(L"hers");
    ac_trie.Add(L"his");
    ac_trie.Add(L"she");
    ac_trie.Add(L"he");
    ac_trie.Add(L"sh");
    ac_trie.Add(L"s");
    ac_trie.Add(L"h");
    ac_trie.Add(L"hr");
    ac_trie.Add(L"hi");

    ac_trie.Remove(L"his");
    is_in = ac_trie.Search(L"hi");
    if(!is_in){
        std::wcout << "Wrong!   hi should exist after remove his" << std::endl; 
    } 
    ac_trie.Add(L"his");

    std::wcout << "Searching" << std::endl;
    is_in = ac_trie.Search(L"his");
    if(!is_in){
        std::wcout << "Wrong!   his should exist" << std::endl; 
    }

    is_in = ac_trie.Search(L"she");
    if(!is_in){
        std::wcout << "Wrong!   she should exist" << std::endl; 
    }

    std::wcout << "Searching" << std::endl;
    is_in = ac_trie.Search(L"shi");
    if(is_in){
        std::wcout << "Wrong!   hi should not exist" << std::endl; 
    }

    std::wcout << "Parsing" << std::endl;
    std::vector<std::pair<size_t,std::wstring>> parsed = ac_trie.ParseText(L"ushers");
    std::wcout << "output" << std::endl;
    for(auto i = 0; i < parsed.size(); i++){
        std::wcout << parsed[i].first << ":" << parsed[i].second << ", " ;
    }
    std::wcout << std::endl;

    ac_trie.Add(L"algorithm");
    ac_trie.Add(L"defines");
    ac_trie.Add(L"functions");
    ac_trie.Add(L"designed");
    ac_trie.Add(L"elements");
    ac_trie.Add(L"header");
    ac_trie.Add(L"lo");
    ac_trie.Add(L"love");
    ac_trie.Add(L"china");
    parsed = ac_trie.ParseText(L"The header <algorithm> defines a collection of functions especially designed to be used on ranges of elements Ilovechina. ");
    for(auto i = 0; i < parsed.size(); i++){
        std::wcout << parsed[i].first << ":" << parsed[i].second << ", " ;
    }
    std::wcout << "\n" << std::endl;
}


void test_ds(){
    test_heap();
    test_Trie();
    test_KVTrie();
    test_ACTrie();
}