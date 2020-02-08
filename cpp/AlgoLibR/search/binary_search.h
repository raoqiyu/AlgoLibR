/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-09 14:55:06
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/search/binary_search.h
 * @Description: 
 */

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include "AlgoLibR/search/utils.h"


namespace AlgoLibR{
namespace search{
namespace binary_search{

template<typename T>
size_t binarySearchKernel(T arr[], T target, long low, long high, comparator::number::CompareFunc<T> compFunc);

template<typename T>
long long binarySearchKernel(T arr[], T target, long low, long high, bool isExist, comparator::number::CompareFunc<T> compFunc);

template<typename T>
long long binarySearchKernel(T arr[], T target, size_t n, bool isExist, comparator::number::CompareFunc<T> compFunc);

} // namespace binary_search
} // namespace SEARCH
} // namespace AlgoLibR

#endif