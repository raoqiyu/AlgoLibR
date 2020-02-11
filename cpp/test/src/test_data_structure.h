/*
Author: raoqiyu@gmail.com
Date: 2020-02-07 17:07:11
FilePath: /AlgoLibR/cpp/test/AlgoLibR/test_data_structure.h
Description: 
 */

#include <stdio.h>
#include <iostream>
#include "AlgoLibR/data_structure/heap.h"
#include "AlgoLibR/data_structure/tree/trie_tree.h"



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

    AlgoLibR::data_structure::tree::trie::Trie<int> str_trie;

    str_trie.Add("hello", 1);
    str_trie.Add("world", 1);

    if(!str_trie.Search("hello")){
        std::cout << "Wrong!" << std::endl;
    }

    if(!str_trie.Search("world")){
        std::cout << "Wrong!" << std::endl;
    }
    
    if(str_trie.Search("he")){
        std::cout << "Wrong!" << std::endl;
    }

    if(str_trie.Search("wor")){
        std::cout << "Wrong!" << std::endl;
    }

    if(str_trie.Search("word")){
        std::cout << "Wrong!" << std::endl;
    }

    std::cout << "\n" << std::endl;
}


void test_ds(){
    test_heap();
    test_Trie();
}