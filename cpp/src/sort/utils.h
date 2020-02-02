/*
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/cpp/src/sort/utils.h
Description: 
 */
#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include<stdlib.h>
#include"utils/comparator.hpp"
#include"utils/register_types.h"


namespace SORT{
    enum SORT_METHOD{
        BUBBLE_SORT_M=0, INSERTION_SORT_M, QUICK_SORT_M, SELECTION_SORT_M, COUNT_SORT_M,
        RADIX_SORT_M, HEAP_SORT_M
    };

    namespace UTILS{

        template<typename T>
        void swap(T *x, T *y){
            T temp = *x;
            *x = *y;
            *y = temp;
        }
    }
}

#endif