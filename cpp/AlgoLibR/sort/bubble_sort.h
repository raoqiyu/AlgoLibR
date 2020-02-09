/*
Author: raoqiyu@gmail.com
Date: 2020-01-14 14:38:30
FilePath: /AlgoLibR/cpp/AlgoLibR/sort/bubble_sort.h
Description: 
 */

#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "AlgoLibR/sort/utils.h"

namespace AlgoLibR{
namespace sort{
namespace bubble_sort{

template<typename T>
void bubbleSortKernel(T arr[], size_t n, comparator::number::CompareFunc<T>compFunc);

} // namespace bubble_sort
} // namespace sort
} // namespace AlgoLibR

#endif