/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 14:50:45
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/radix_sort.cpp
 * @Description: 
 */

#include "AlgoLibR/sort/radix_sort_cpu.h"
#include "AlgoLibR/framework/comparator.hpp"

namespace AlgoLibR{
namespace sort{
namespace radix_sort_cpu{

template<typename T>
void radixSortKernel(T arr[], size_t n, bool ascending){
    T max_ele = comparator::array::max(arr, n);
    int max_exp = 1;
    while(max_ele/max_exp > 0){
        max_exp *=10;
    }
    int exp = 1;
    for(; exp  < max_exp; exp *= 10){
        sort::count_sort::radixCountSortKernel(arr, n, exp, true);
    }
    sort::count_sort::radixCountSortKernel(arr, n, exp, ascending); 
}


#define DEFINE_SORT_KERNELS(T) \
    template void radixSortKernel<T>(T arr[], size_t n, bool ascending);
REGISTER_INTEGER_TYPES(DEFINE_SORT_KERNELS); 

} // namespace radix_sort_cpu
} // namespace sort
} // namespace AlgoLibR
