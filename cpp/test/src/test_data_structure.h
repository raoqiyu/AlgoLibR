/*
Author: raoqiyu@gmail.com
Date: 2020-02-07 17:07:11
FilePath: /AlgoLibR/cpp/test/src/test_data_structure.h
Description: 
 */


#include "data_structure/heap.h"
#include <stdio.h>


void test_heap(){
    printf("Test Heap\n");

    DATA_STRUCTURE::HEAP::HeapImp<int> heap = DATA_STRUCTURE::HEAP::HeapImp<int>(5,true);

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
