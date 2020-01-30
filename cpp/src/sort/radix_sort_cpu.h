/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 14:44:22
 * @FilePath: /AlgoLibR/cpp/src/sort/radix_sort_cpu.h
 * @Description: 
 */

#ifndef RADIX_SORT_CPU_H
#define RADIX_SORT_CPU_H

#include "array/compare.h"
#include "sort/count_sort.h"
#include "utils/register_types.h"

namespace SORT{
    namespace RADIX_SORT_CPU{

        template<typename T>
        void radixSortKernel(T arr[], size_t n, bool ascending);
    } // RADIX_SORT_CPU
} // SORT

#endif

