/*
@Author: raoqiyu@gmail.com
@Time: 2020-01-08 15:21:23
@File: sort_kernel_imp.h
*/

#ifndef ALGO_SERCH_KERNEL_IMPL_H_
#define ALGO_SERCH_KERNEL_IMPL_H_

#include "binary_search.cpp"

namespace SEARCH{

#define DEFINE_SEARCH_KERNELS(T)                                                          \
    template size_t SEARCH::BINARY_SEARCH::binarySearchKernel<T>(T arr[], T target, long low, long high);

DEFINE_SEARCH_KERNELS(short);
DEFINE_SEARCH_KERNELS(unsigned short);
DEFINE_SEARCH_KERNELS(unsigned int);
DEFINE_SEARCH_KERNELS(long);
DEFINE_SEARCH_KERNELS(unsigned long);
DEFINE_SEARCH_KERNELS(long long);
DEFINE_SEARCH_KERNELS(unsigned long long);
DEFINE_SEARCH_KERNELS(float);
DEFINE_SEARCH_KERNELS(double);

}

#endif //ALGO_SERCH_KERNEL_IMPL_H_
