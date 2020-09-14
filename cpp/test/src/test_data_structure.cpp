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
#include "AlgoLibR/data_structure/trie/trie_tree.h"
#include "AlgoLibR/data_structure/trie/kv_trie_tree.h"
#include "AlgoLibR/data_structure/trie/ac_trie.h"
#include <gtest/gtest.h>

bool test_max(std::pair<int,int> x, std::pair<int,int> y){
    return x.second > y.second;
}


TEST(test_data_structure,heap){
    printf("Test Heap\n");

    AlgoLibR::data_structure::heap::HeapImp<int> heap(5, true);

    heap.insert(2);
    heap.insert(100);
    heap.insert(1);
    heap.insert(45);
    heap.insert(6);

    ASSERT_EQ(heap.get(), 100);
    heap.remove();
    ASSERT_EQ(heap.get(), 45);
    heap.remove();
    ASSERT_EQ(heap.get(), 6);
    heap.remove();
    ASSERT_EQ(heap.get(), 2);
    heap.remove();
    ASSERT_EQ(heap.get(), 1);
    heap.remove();
    ASSERT_EQ(heap.size(), 0);

    int arr[5]  = {2, 100, 1 ,45, 6};
    int * result, k=2;

    result = AlgoLibR::data_structure::heap::klargest(arr, 5, k);
    ASSERT_EQ(result[0], 100);
    ASSERT_EQ(result[1], 45);

    if(result != nullptr){
        delete result;
    }
    
    result = AlgoLibR::data_structure::heap::ksmallest(arr, 5, k);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);

    std::wcout << std::endl;
    if(result != nullptr){
        delete result;
    }
}


TEST(test_data_structure, Trie){
    std::wcout << "Test Trie" << std::endl;

    AlgoLibR::data_structure::trie::trie::Trie<AlgoLibR::data_structure::trie::trie::TrieNode> str_trie;

    str_trie.Add(L"hello");
    str_trie.Add(L"world");
    str_trie.Add(L"我");

    ASSERT_TRUE(str_trie.Search(L"hello"));
    ASSERT_TRUE(str_trie.Search(L"world"));
    ASSERT_FALSE(str_trie.Search(L"he"));
    ASSERT_FALSE(str_trie.Search(L"wr"));
    ASSERT_TRUE(str_trie.Search(L"我"));

    str_trie.Add(L"his");
    str_trie.Add(L"hi");
    ASSERT_TRUE(str_trie.Search(L"hi"));
    
    str_trie.Remove(L"his");
    ASSERT_TRUE(str_trie.Search(L"hi"));

    str_trie.Add(L"我们");
    ASSERT_TRUE(str_trie.Search(L"我"));

    str_trie.Remove(L"我");
    ASSERT_FALSE(str_trie.Search(L"我"));

    str_trie.Remove(L"我");
    ASSERT_FALSE(str_trie.Search(L"我"));
    ASSERT_TRUE(str_trie.Search(L"我们"));
}

void test_KVTrie(){
    std::wcout << "Test KVTrie" << std::endl <<     std::flush;
    AlgoLibR::data_structure::trie::kv_trie::KVTrie<wchar_t*> str_trie;

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
    AlgoLibR::data_structure::trie::ac_trie::ACTrie ac_trie;

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
    test_KVTrie();
    test_ACTrie();
}