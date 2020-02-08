/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 13:46:52
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/count_sort.h
 * @Description: 
 */

#ifndef COUNT_SORT_H
#define COUNT_SORT_H

#include "AlgoLibR/sort/utils.h"
#include "AlgoLibR/array/compare.h"

namespace AlgoLibR{
namespace sort{
namespace count_sort{
    
template<typename T>
void countSortKernel(T arr[], size_t n, bool ascending);

template<typename T>
void radixCountSortKernel(T arr[], size_t n, int exp, bool ascending);

} // namespace COUNT_SORT
} // namespace sort
} // namespace AlgoLibR


#endif 
