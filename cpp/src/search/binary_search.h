/*
 * @Author: raoqiyu@mail.com
 * @Date: 2020-01-09 14:55:06
 * @FilePath: /AlgoLibR/cpp/src/search/binary_search.h
 * @Description: 
 */
#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include "search/utils.h"

namespace SEARCH{
    namespace BINARY_SEARCH{

    template<typename T>
    size_t binarySearchKernel(T arr[], T target, long low, long high, COMPARATOR::NUMBER::CompareFunc<T> compFunc);

    template<typename T>
    long long binarySearchKernel(T arr[], T target, long low, long high, bool isExist, COMPARATOR::NUMBER::CompareFunc<T> compFunc);

    template<typename T>
    long long binarySearchKernel(T arr[], T target, size_t n, bool isExist, COMPARATOR::NUMBER::CompareFunc<T> compFunc);



    }
}

#endif