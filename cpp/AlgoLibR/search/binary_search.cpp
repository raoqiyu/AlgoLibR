/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-09 14:55:06
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/search/binary_search.cpp
 * @Description: 
 */

#include "AlgoLibR/search/binary_search.h"
#include "AlgoLibR/framework/comparator.hpp"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace search{
namespace binary_search{

template<typename T>
size_t binarySearchKernel(T arr[], T target, long low, long high, comparator::number::CompareFunc<T> compFunc){
    if(low >= high){
        return (compFunc(target, arr[low])) ? low+1:low;
    }
    long mid = low + (high-low)/2;

    if(target == arr[mid]){
        return mid;
    } else if(compFunc(target,arr[mid])){
        return binarySearchKernel(arr, target, mid+1, high, compFunc);
    } else {
        return binarySearchKernel(arr, target, low, mid-1, compFunc);
    }
}

template<typename T>
size_t binarySearchKernel(T arr[], T target, long low, long high, bool ascending){
    comparator::number::CompareFunc<T> compFunc = comparator::number::less<T>;
    if(ascending){
        compFunc = comparator::number::greater<T>;
    }

    return binarySearchKernel(arr, target, low, high, compFunc);
}

template<typename T>
long long binarySearchKernel(T arr[], T target, long low, long high, bool isExist, comparator::number::CompareFunc<T> compFunc){ 
    size_t pos2insert = binarySearchKernel(arr, target, low, high, compFunc);
    if( !isExist or (arr[pos2insert] == target)){
        // not need to judge where target in exist in arr
        return pos2insert;
    }
    // find the position where target exists, if not exists return -1
    if( (pos2insert == low) or (pos2insert == (high+1))){
        // the position to insert target is 0 or n, target is not in the arr
        return -1;
    }else if(arr[pos2insert-1] == target ){
        // target is before arr[pos2insert]
        return pos2insert-1;
    }else{
        // target is after arr[pos2insert]
        return pos2insert+1;
    } 

}

template<typename T>
long long binarySearchKernel(T arr[], T target, size_t n, bool isExist, comparator::number::CompareFunc<T> compFunc){
    return binarySearchKernel(arr, target, 0, n-1, isExist, compFunc);
}

template<typename T>
long long binarySearchKernel(T arr[], T target, size_t n, bool isExist, bool ascending){
    comparator::number::CompareFunc<T> compFunc = comparator::number::less<T>;
    if(ascending){
        compFunc = comparator::number::greater<T>;
    }
 
    return binarySearchKernel(arr, target, 0, n-1, isExist, compFunc);
}



#define DEFINE_SEARCH_KERNELS(T) \
    template size_t binarySearchKernel<T>(T arr[], T target, long low, long high, comparator::number::CompareFunc<T> compFunc); \
    template size_t binarySearchKernel<T>(T arr[], T target, long low, long high, bool ascending); \
    template long long  binarySearchKernel<T>(T arr[], T target, long low, long high, bool isExist, comparator::number::CompareFunc<T> compFunc); \
    template long long binarySearchKernel<T>(T arr[], T target, size_t n, bool isExist, comparator::number::CompareFunc<T> compFunc); \
    template long long binarySearchKernel<T>(T arr[], T target, size_t n, bool isExist, bool ascending);
REGISTER_REAL_NUMBER_TYPES(DEFINE_SEARCH_KERNELS);

} //namespace binary_search
} // namespace SEARCH
} // namespace AlgoLibR