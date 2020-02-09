/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-14 14:38:30
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/quick_sort.h
 * @Description: 
 */

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "AlgoLibR/sort/utils.h"

namespace AlgoLibR{
namespace sort{
namespace quick_sort{

template<typename T>
long partition(T arr[], long low, long high, comparator::number::CompareFunc<T>compFunc);

template<typename T>
void quickSortKernel(T arr[], size_t n, comparator::number::CompareFunc<T>compFunc);

template<typename T>
void quickSortKernel(T arr[], long low, long high, comparator::number::CompareFunc<T>compFunc);

} // namespace quick_sort
} // namespace sort
} // namespace AlgoLibR

#endif