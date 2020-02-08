/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-14 14:38:30
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/insertion_sort.h
 * @Description: 
 */

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "AlgoLibR/sort/utils.h"
#include "AlgoLibR/search/binary_search.h"


namespace AlgoLibR{
namespace sort{
namespace insertion_sort{

template<typename T>
void insertionSortKernel(T arr[], size_t n, comparator::number::CompareFunc<T> compFunc);

} // namespace insertion_sort
} // namespace sort
} // namespace AlgoLibR

#endif
