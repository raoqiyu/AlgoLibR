/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-14 14:38:56
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/framework/comparator.hpp
 * @Description: 
 */
#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <stdlib.h>

namespace AlgoLibR{
namespace comparator{
namespace array{

// typedef bool  (*CompareFunc) (void* data, long long i, long long  j);    // Compare data[i] and data[j]

// template<typename T>
// bool greater(void *data, long long  i, long long  j){
//     return ((T*)data)[i] > ((T*)data)[j];        
// }

// template<typename T>
// bool less(void *data, long long i, long long j){
//     return ((T*)data)[i] < ((T*)data)[j];        
// }

template<typename T>
T max(T arr[], size_t n){
    if(n <= 0){
        return 0;
    }
    T target = arr[0];
    for(auto i = 1; i < n; i++){
        if(arr[i] > target){
            target = arr[i];
        }
    } // for
    return target;
}

template<typename T>
T min(T arr[], size_t n){
    if(n <= 0){
        return 0;
    }
    T target = arr[0];
    for(auto i = 1; i < n; i++){
        if(arr[i] < target){
            target = arr[i];
        }
    } // for
    return target;
}

} // namespace array 

namespace number{
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


} // namespace number 
} // namespace comparator
} // namespace AlgoLibR
#endif