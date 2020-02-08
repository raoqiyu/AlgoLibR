/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-15 09:15:31
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/sort.hpp
 * @Description: 
 */

#include "AlgoLibR/sort/sort.h"
#include "AlgoLibR/sort/bubble_sort.h"
#include "AlgoLibR/sort/insertion_sort.h"
#include "AlgoLibR/sort/quick_sort.h"
#include "AlgoLibR/sort/selection_sort.h"
#include "AlgoLibR/sort/count_sort.h"
#include "AlgoLibR/sort/radix_sort_cpu.h"
#include "AlgoLibR/sort/heap_sort.h"
#include "AlgoLibR/sort/merge_sort.h"
#include "AlgoLibR/sort/tim_sort.h"


namespace AlgoLibR{
namespace sort{

template<typename T>
void sortKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending){
    if(n == 0){
        return ;
    }
    comparator::array::CompareFunc compFunc = comparator::array::less<T>;
    comparator::number::CompareFunc<T> compFuncNum = comparator::number::less<T>; 
    if(ascending){
        compFunc = comparator::array::greater<T>;
        compFuncNum = comparator::number::greater<T>;

    }

    switch(method){
        case BUBBLE_SORT_M:
            sort::bubble_sort::bubbleSortKernel(arr, n, compFunc);
            break;
        case QUICK_SORT_M:
            sort::quick_sort::quickSortKernel(arr, n, compFunc);
            break;
        case SELECTION_SORT_M:
            sort::selection_sort::selectionSortKernel(arr, n, compFunc);
            break;
        case INSERTION_SORT_M:
            sort::insertion_sort::insertionSortKernel(arr, n, compFuncNum);
            break;
        case HEAP_SORT_M:
            sort::heap_sort::heapSortKernel(arr, n, ascending);
            break;
        case MERGE_SORT_M:
            sort::merge_sort::mergeSortKernel(arr, n, ascending);
        case TIM_SORT_M:
            sort::tim_sort::timSortKernel(arr, n, ascending);
        default:
            sort::bubble_sort::bubbleSortKernel(arr, n, compFunc);
    };
}

template<typename T>
void sortIntegerKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending){
    if(n == 0){
        return ;
    }
    switch(method){
            case COUNT_SORT_M:
            sort::count_sort::countSortKernel(arr, n, ascending);
            break;
        case RADIX_SORT_M:
            sort::radix_sort_cpu::radixSortKernel(arr, n, ascending);
            break;
        default:
            sort::count_sort::countSortKernel(arr, n, ascending);      
    }
}
#define DEFINE_SORT_KERNELS(T) \
    template void sortKernel<T>(T arr[], size_t n, enum SORT_METHOD method, bool ascending);
REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);

#define DEFINE_SORT_KERNELS(T) \
    template void sortIntegerKernel<T>(T arr[], size_t n, enum SORT_METHOD method, bool ascending);
REGISTER_INTEGER_TYPES(DEFINE_SORT_KERNELS);

} // namespace sort
} // namespace AlgoLibR