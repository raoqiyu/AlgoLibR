/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-02 15:06:35
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/heap_sort.h
 * @Description: 
 */

#ifndef heap_sort_H
#define heap_sort_H

#include <stdlib.h>

namespace AlgoLibR{
namespace sort{
namespace heap_sort{

template<typename T>
void heapSortKernel(T arr[], size_t n, bool ascending);

} // namespace heap_sort
} // namespace sort
} // namespace AlgoLibR

#endif
