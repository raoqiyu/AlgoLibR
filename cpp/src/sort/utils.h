#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include<stdlib.h>
#include"utils/comparator.hpp"

namespace SORT{
    enum SORT_METHOD{
        BUBBLE_SORT_M=0, INSERTION_SORT_M, QUICK_SORT_M, SELECTION_SORT_M
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