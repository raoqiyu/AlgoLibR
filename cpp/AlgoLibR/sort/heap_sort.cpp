/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-02 15:09:16
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/heap_sort.cpp
 * @Description: 
 */

#include "AlgoLibR/sort/heap_sort.h"
#include "AlgoLibR/sort/utils.h"
#include "AlgoLibR/data_structure/heap.h"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace sort{
namespace heap_sort{

template<typename T>
void heapSortKernel(T arr[], size_t n, bool ascending){
    // build heap 
    data_structure::heap::build_heap(arr, n, ascending);
    // one by one extract element from heap 
    for(long long i = n-1; i >= 0; i--){
        sort::UTILS::swap<T>(&arr[0], &arr[i]);

        data_structure::heap::heapify(arr, i, 0, ascending);
    }
}

#define DEFINE_SORT_KERNELS(T) \
    template void heapSortKernel<T>(T arr[], size_t n, bool ascending);
REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);

} // namespace heap_sort
} // namespace sort
} // namespace AlgoLibR

