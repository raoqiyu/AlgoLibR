/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-02 15:09:16
 * @FilePath: /AlgoLibR/cpp/src/sort/heap_sort.cpp
 * @Description: 
 */

#include "sort/heap_sort.h"
#include "sort/utils.h"
#include "data_structure/heap.h"
#include "utils/register_types.h"

namespace SORT{
    namespace HEAP_SORT{

        template<typename T>
        void heapSortKernel(T arr[], size_t n, bool ascending){
            // build heap 
            DATA_STRUCTURE::HEAP::build_heap(arr, n, ascending);
            // one by one extract element from heap 
            for(long long i = n-1; i >= 0; i--){
                SORT::UTILS::swap<T>(&arr[0], &arr[i]);

                DATA_STRUCTURE::HEAP::heapify(arr, i, 0, ascending);
            }
        }

        #define DEFINE_SORT_KERNELS(T) \
            template void heapSortKernel<T>(T arr[], size_t n, bool ascending);
        REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);
    } //HEAP_SORT
} //SORT

