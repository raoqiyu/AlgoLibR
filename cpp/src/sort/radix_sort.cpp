/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 14:50:45
 * @FilePath: /AlgoLibR/cpp/src/sort/radix_sort.cpp
 * @Description: 
 */

#include "sort/radix_sort_cpu.h"

namespace SORT{
    namespace RADIX_SORT_CPU{

        template<typename T>
        void radixSortKernel(T arr[], size_t n, bool ascending){
            T max_ele = ARRAY::COMPARE::max(arr, n);
            int max_exp = 1;
            while(max_ele/max_exp > 0){
                max_exp *=10;
            }
            int exp = 1;
            for(; exp  < max_exp; exp *= 10){
                SORT::COUNT_SORT::radixCountSortKernel(arr, n, exp, true);
            }
            SORT::COUNT_SORT::radixCountSortKernel(arr, n, exp, ascending); 
        }
        
        #define DEFINE_SORT_KERNELS(T) \
            template void radixSortKernel<T>(T arr[], size_t n, bool ascending);
        REGISTER_INTEGRAL_TYPES(DEFINE_SORT_KERNELS); 
    }
}
