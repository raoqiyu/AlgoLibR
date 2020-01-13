#include "selection_sort.h"


namespace SORT{
    namespace SELECTION_SORT{
        /*The selection sort algorithm sorts an array by repeatedly find the minimum elemments(considering ascending order)
        from unsorted part and putting it at the beging. The algorithm maintains two subarrays in a given array:
        1) The subarray which is already sorted.
        2) Remaining subarray which is unsorted.
        */
        template<typename T>
        void unstableSelectionSortKernel(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc){
            size_t i,j,target_ele_idx;
            // a[0]...a[i-1] is the sorted subarray
            for(i = 0; i < n-1; i++){
                target_ele_idx = i;
                // a[i]...a[n-1] is the unsorted subarray
                for( j = i+1; j < n; j++){
                    // find the minimum element from the unsorted subarray
                    if(compFunc(arr, target_ele_idx, j)){
                        target_ele_idx = j;
                    }
                }
                // append the minimum element of the unsorted subarray to the sorted subarray
                // NOTE: this swap operation makes selection sort algorithm unstable
                SORT::UTILS::swap<T>(&arr[i],&arr[target_ele_idx]);

            }
        }
        template<typename T>
        void stableSelectionSortKernel(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc){
            size_t i,j,target_ele_idx;
            // a[0]...a[i-1] is the sorted subarray
            for(i = 0; i < n-1; i++){
                target_ele_idx = i;
                // a[i]...a[n-1] is the unsorted subarray
                for( j = i+1; j < n; j++){
                    // find the minimum element from the unsorted subarray
                    if(compFunc(arr, target_ele_idx, j)){
                        target_ele_idx = j;
                    }
                    // append the minimum element of the unsorted subarray to the sorted subarray
    //                if(target_ele_idx != i){
    //                    // NOTE: this swap operation makes selection sort algorithm unstable
    //                    SORT::UTILS::swap<T>(&arr[i],&arr[target_ele_idx]);
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
        void selectionSortKernel(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc){
            unstableSelectionSortKernel(arr, n, compFunc);
        }
    } //SELECTION_SORT
} //SORT


