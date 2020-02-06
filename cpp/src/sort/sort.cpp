/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-15 09:15:31
 * @FilePath: /AlgoLibR/cpp/src/sort/sort.hpp
 * @Description: 
 */
/*
@Author: raoqiyu@gmail.com
@Time: 2019-12-13 17:10:09
@File: sort.h
*/

#include "sort/sort.h"
#include "bubble_sort.h"
#include "insertion_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"
#include "count_sort.h"
#include "radix_sort_cpu.h"
#include "heap_sort.h"
#include "merge_sort.h"


namespace SORT{

    template<typename T>
    void sortKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending){
        if(n == 0){
            return ;
        }
        COMPARATOR::ARRAY::CompareFunc compFunc = COMPARATOR::ARRAY::less<T>;
        COMPARATOR::NUMBER::CompareFunc<T> compFuncNum = COMPARATOR::NUMBER::less<T>; 
        if(ascending){
            compFunc = COMPARATOR::ARRAY::greater<T>;
            compFuncNum = COMPARATOR::NUMBER::greater<T>;

        }

        switch(method){
            case BUBBLE_SORT_M:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n, compFunc);
                break;
            case QUICK_SORT_M:
                SORT::QUICK_SORT::quickSortKernel(arr, n, compFunc);
                break;
            case SELECTION_SORT_M:
                SORT::SELECTION_SORT::selectionSortKernel(arr, n, compFunc);
                break;
            case INSERTION_SORT_M:
                SORT::INSERTION_SORT::insertionSortKernel(arr, n, compFuncNum);
                break;
            case HEAP_SORT_M:
                SORT::HEAP_SORT::heapSortKernel(arr, n, ascending);
                break;
            case MERGE_SORT_M:
                SORT::MERGE_SORT::mergeSortKernel(arr, n, ascending);
            default:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n, compFunc);
        };
    }

    template<typename T>
    void sortIntegerKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending){
        if(n == 0){
            return ;
        }
        switch(method){
             case COUNT_SORT_M:
                SORT::COUNT_SORT::countSortKernel(arr, n, ascending);
                break;
            case RADIX_SORT_M:
                SORT::RADIX_SORT_CPU::radixSortKernel(arr, n, ascending);
                break;
            default:
                SORT::COUNT_SORT::countSortKernel(arr, n, ascending);      
        }
    }
    #define DEFINE_SORT_KERNELS(T) \
        template void sortKernel<T>(T arr[], size_t n, enum SORT_METHOD method, bool ascending);
    REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);

    #define DEFINE_SORT_KERNELS(T) \
        template void sortIntegerKernel<T>(T arr[], size_t n, enum SORT_METHOD method, bool ascending);
    REGISTER_INTEGER_TYPES(DEFINE_SORT_KERNELS);
} //SORT