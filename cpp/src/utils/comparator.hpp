/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-14 14:38:56
 * @FilePath: /AlgoLibR/cpp/src/utils/comparator.hpp
 * @Description: 
 */
#ifndef COMPARATOR_H
#define COMPARATOR_H

#include<stdlib.h>

namespace COMPARATOR{
    namespace ARRAY{
        typedef bool  (*CompareFunc) (void* data, long long i, long long  j);    // Compare data[i] and data[j]

        template<typename T>
        bool greater(void *data, long long  i, long long  j){
            return ((T*)data)[i] > ((T*)data)[j];        
        }
        
        template<typename T>
        bool less(void *data, long long i, long long j){
            return ((T*)data)[i] < ((T*)data)[j];        
        }
    } // array 

    namespace NUMBER{
        template<typename T> using CompareFunc = bool (*) (T x, T y);    // Compare x and y

        template<typename T>
        bool greater(T x, T y){
            return x > y;        
        }

        template<typename T>
        bool greater_equal(T x, T y){
            return x >= y;        
        }


        template<typename T>
        bool less(T x, T y){
            return x < y;        
        }

        template<typename T>
        bool less_equal(T x, T y){
            return x <= y;        
        }

        template<typename T>
        bool max(T x, T y){
            if(x > y){
                return x;
            }else{
                return y;
            }         
        }

        template<typename T>
        bool min(T x, T y){
            if(x < y){
                return x;
            }else{
                return y;
            }
        }
        

    } // number 

} // COMPARATOR

#endif