/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-06 18:48:17
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/merge_sort.h
 * @Description: 
 */

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdlib.h>
#include "AlgoLibR/framework/comparator.hpp"

namespace AlgoLibR{
namespace sort{
namespace merge_sort{
    
template<typename T>
void merge(T arr[], size_t low, size_t middle, size_t high, comparator::number::CompareFunc<T> compFunc);

template<typename T>
void mergeSortKernel(T arr[], size_t low, size_t high, comparator::number::CompareFunc<T> compFunc);

template<typename T>
void mergeSortKernel(T arr[], size_t n, bool ascending);


} // namespace merge_sort
} // namespace sort
} // namespace AlgoLibR


#endif
