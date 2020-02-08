/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-07 15:23:16
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/tim_sort.cpp
 * @Description: 
 */

#include "AlgoLibR/sort/tim_sort.h"
#include "AlgoLibR/sort/merge_sort.h"
#include "AlgoLibR/sort/insertion_sort.h"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace sort{
namespace tim_sort{

// First sort small pieces using Insertion Sort, then merges the pieces using merge of merge sort.
template<typename T>
void timSortKernel(T arr[], size_t n, bool ascending){
    comparator::number::CompareFunc<T> compFunc = comparator::number::less_equal<T>; 
    if(ascending){
        compFunc = comparator::number::greater_equal<T>;
    }
    
    // sort subarrays of size tim_split_size
    for(auto i = 0; i < n; i += tim_split_size){
        size_t subarray_size = comparator::number::min(tim_split_size, n-i);
        sort::insertion_sort::insertionSortKernel(&arr[i], subarray_size, compFunc);
    }

    // merge subarrays of size tim_split_size
    // then mege subarrays of size tim_split_size*2, 
    // then mege subarrays of size tim_split_size*4 and so on
    // It will merge to form size 2*tim_split_size, 4*tim_split_size, .....
    for(auto size = tim_split_size; size < n; size *=2 ){
        // merge arr[left:left+size-1] and arr[left+size:left+2*size-1]
        // then merge arr[left+2*size:left+2*size+size-1] and arr[left+2*size+size:left+4*size-1] 
        // then merge arr[left+4*size:left+4*size+size-1] and arr[left+4*size+size:left+6*size-1]
        // increase left by 2*size at each iteration
        for(auto left = 0; left < n; left += 2*size){
            size_t mid = left + size - 1;
            size_t right = comparator::number::min((left + 2*size -1), n-1);
            
            // merge arr[left:mid] and arr[mid+1:right]
            sort::merge_sort::merge(arr, left, mid, right, compFunc);
        }
    } 
}


#define DEFINE_SORT_KERNELS(T) \
    template void timSortKernel<T>(T arr[], size_t n, bool ascending);  
REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);

} // namespace tim_sort
} // namespace sort
} // namespace AlgoLibR
