/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-06 18:48:17
 * @FilePath: /AlgoLibR/cpp/src/sort/merge_sort.h
 * @Description: 
 */

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdlib.h>
#include"utils/comparator.hpp"


namespace SORT{
    namespace MERGE_SORT{
        
        template<typename T>
        void merge(T arr[], size_t low, size_t middle, size_t high, COMPARATOR::NUMBER::CompareFunc<T> compFunc);

        template<typename T>
        void mergeSortKernel(T arr[], size_t low, size_t high, COMPARATOR::NUMBER::CompareFunc<T> compFunc);

        template<typename T>
        void mergeSortKernel(T arr[], size_t n, COMPARATOR::NUMBER::CompareFunc<T> compFunc);


    } // MERGE_SORT
} // SORT


#endif
