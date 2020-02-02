/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-02 15:06:35
 * @FilePath: /AlgoLibR/cpp/src/sort/heap_sort.h
 * @Description: 
 */

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <stdlib.h>

namespace SORT{
    namespace HEAP_SORT{
        template<typename T>
        void heapSortKernel(T arr[], size_t n, bool ascending);
    } //HEAP_SORT
} //SORT

#endif
