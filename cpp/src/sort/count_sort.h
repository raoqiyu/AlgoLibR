/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 13:46:52
 * @FilePath: /AlgoLibR/cpp/src/sort/count_sort.h
 * @Description: 
 */

#ifndef COUNT_SORT_H
#define COUNT_SORT_H

#include "sort/utils.h"
#include "array/compare.h"

namespace SORT{
    namespace COUNT_SORT{
        
        template<typename T>
        void countSortKernel(T arr[], size_t n, bool ascending);
        
        template<typename T>
        void radixCountSortKernel(T arr[], size_t n, int exp, bool ascending);
    } // COUNT_SORT
} // SORT


#endif 
