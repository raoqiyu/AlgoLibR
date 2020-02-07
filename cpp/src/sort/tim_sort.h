/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-07 15:20:34
 * @FilePath: /AlgoLibR/cpp/src/sort/tim_sort.h
 * @Description: 
 */

#ifndef TIM_SORT_H
#define TIM_SORT_H


#include <stdlib.h>

namespace SORT{
    namespace TIM_SORT{
        const size_t tim_split_size = 128;

        template<typename T>
        void timSortKernel(T arr[], size_t n, bool ascending);
    } // TIM_SORT
} // SORT
#endif
