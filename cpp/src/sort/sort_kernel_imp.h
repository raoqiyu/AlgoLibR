/*
@Author: raoqiyu@gmail.com
@Time: 2020-01-08 15:21:23
@File: sort_kernel_imp.h
*/

#ifndef ALGO_SORT_KERNEL_IMPL_H_
#define ALGO_SORT_KERNEL_IMPL_H_

#include "bubble_sort.cpp"
#include "insertion_sort.cpp"
#include "quick_sort.cpp"
#include "selection_sort.cpp"


namespace SORT{

#define DEFINE_SORT_KERNELS(T)                                                          \
    template void SORT::BUBBLE_SORT::bubbleSortKernel<T>(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc);            \
    template void SORT::INSERTION_SORT::insertionSortKernel<T>(T arr[], size_t n);      \
    template void SORT::QUICK_SORT::quickSortKernel<T>(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc);              \
    template void SORT::SELECTION_SORT::selectionSortKernel<T>(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc);

DEFINE_SORT_KERNELS(short);
DEFINE_SORT_KERNELS(unsigned short);
DEFINE_SORT_KERNELS(unsigned int);
DEFINE_SORT_KERNELS(long);
DEFINE_SORT_KERNELS(unsigned long);
DEFINE_SORT_KERNELS(long long);
DEFINE_SORT_KERNELS(unsigned long long);
DEFINE_SORT_KERNELS(float);
DEFINE_SORT_KERNELS(double);
}

#endif //ALGO_SORT_KERNEL_IMPL_H_
