/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 14:44:22
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/radix_sort_cpu.h
 * @Description: 
 */

#ifndef RADIX_SORT_CPU_H
#define RADIX_SORT_CPU_H

#include "AlgoLibR/array/compare.h"
#include "AlgoLibR/sort/count_sort.h"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace sort{
namespace radix_sort_cpu{

template<typename T>
void radixSortKernel(T arr[], size_t n, bool ascending);

} // namespace radix_sort_cpu
} // namespace sort
} // namespace AlgoLibR

#endif

