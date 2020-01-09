#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include<stdlib.h>

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

        typedef bool  (*CompareFunc) (void* data, size_t i, size_t j);    // Compare data[i] and data[j]

        template<typename T>
        bool greater(void *data, size_t i, size_t j){
            return ((T*)data)[i] >= ((T*)data)[j];        
        }
        
        template<typename T>
        bool less(void *data, size_t i, size_t j){
            return ((T*)data)[i] < ((T*)data)[j];        
        }

    }
}

#endif