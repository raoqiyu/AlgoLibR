#ifndef COMPARATOR_H
#define COMPARATOR_H

#include<stdlib.h>

namespace COMPARATOR{
    namespace ARRAY{
        typedef bool  (*CompareFunc) (void* data, size_t i, size_t j);    // Compare data[i] and data[j]

        template<typename T>
        bool greater(void *data, size_t i, size_t j){
            return ((T*)data)[i] >= ((T*)data)[j];        
        }
        
        template<typename T>
        bool less(void *data, size_t i, size_t j){
            return ((T*)data)[i] < ((T*)data)[j];        
        }
    } // array 

    namespace NUMBER{
        template<typename T> using CompareFunc = bool (*) (T x, T y);    // Compare x and y

        template<typename T>
        bool greater(T x, T y){
            return x >= y;        
        }
        
        template<typename T>
        bool less(T x, T y){
            return x < y;        
        }
    } // number 

} // COMPARATOR

#endif