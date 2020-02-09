/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-14 14:38:30
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/selection_sort.cpp
 * @Description: 
 */

#include "AlgoLibR/sort/selection_sort.h"

namespace AlgoLibR{
namespace sort{
namespace selection_sort{

/*The selection sort algorithm sorts an array by repeatedly find the minimum elemments(considering ascending order)
from unsorted part and putting it at the beging. The algorithm maintains two subarrays in a given array:
1) The subarray which is already sorted.
2) Remaining subarray which is unsorted.
*/
template<typename T>
void unstableSelectionSortKernel(T arr[], size_t n, comparator::number::CompareFunc<T>compFunc){
    size_t i,j,target_ele_idx;
    // a[0]...a[i-1] is the sorted subarray
    for(i = 0; i < n-1; i++){
        target_ele_idx = i;
        // a[i]...a[n-1] is the unsorted subarray
        for( j = i+1; j < n; j++){
            // find the minimum element from the unsorted subarray
            if(compFunc(arr[target_ele_idx], arr[j])){
                target_ele_idx = j;
            }
        }
        // append the minimum element of the unsorted subarray to the sorted subarray
        // NOTE: this swap operation makes selection sort algorithm unstable
        sort::UTILS::swap<T>(&arr[i],&arr[target_ele_idx]);

    }
}
template<typename T>
void stableSelectionSortKernel(T arr[], size_t n, comparator::number::CompareFunc<T>compFunc){
    size_t i,j,target_ele_idx;
    // a[0]...a[i-1] is the sorted subarray
    for(i = 0; i < n-1; i++){
        target_ele_idx = i;
        // a[i]...a[n-1] is the unsorted subarray
        for( j = i+1; j < n; j++){
            // find the minimum element from the unsorted subarray
            if(compFunc(arr[target_ele_idx], arr[j])){
                target_ele_idx = j;
            }
            // append the minimum element of the unsorted subarray to the sorted subarray
//                if(target_ele_idx != i){
//                    // NOTE: this swap operation makes selection sort algorithm unstable
//                    sort::UTILS::swap<T>(&arr[i],&arr[target_ele_idx]);
//                }
        }
        // if want selection sort be stable, should move elements i,i+1,....,target_ele_idx-1,sequencely
        // but this need more move operation
        T min_ele = arr[target_ele_idx];
        while(target_ele_idx > i){
            arr[target_ele_idx] = arr[target_ele_idx-1];
            target_ele_idx--;
        }
        arr[i] = min_ele;
    }
}

template<typename T>
void selectionSortKernel(T arr[], size_t n, comparator::number::CompareFunc<T>compFunc){
    unstableSelectionSortKernel(arr, n, compFunc);
}


#define DEFINE_SORT_KERNELS(T) \
    template void selectionSortKernel<T>(T arr[], size_t n, comparator::number::CompareFunc<T>compFunc);
REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);

} // namespace selection_sort
} // namespace sort
} // namespace AlgoLibR


