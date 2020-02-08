/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-14 14:38:30
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/selection_sort.h
 * @Description: 
 */

#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "AlgoLibR/sort/utils.h"

namespace AlgoLibR{
namespace sort{
namespace selection_sort{

template<typename T>
void selectionSortKernel(T arr[], size_t n, comparator::array::CompareFunc compFunc);

} // namespace selection_sort
} // namespace sort
} // namespace AlgoLibR

#endif