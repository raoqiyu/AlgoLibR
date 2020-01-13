#include "quick_sort.h"

namespace SORT{
    namespace QUICK_SORT{

        /*This function take the last element as pivot, places the pivot element at its correct position in sorted
        array, and places all smaller (small than pivot) to the left of pivot and all greater elements to the right.
        */
        template<typename T>
        long partition(T arr[], long low, long high, COMPARATOR::ARRAY::CompareFunc compFunc){
            size_t pivot_index = high; // pivot
            long i = low-1; //index of the smaller elements
            for( auto j = low; j < high; j++){
                // if current element is small than the pivot
                if(compFunc(arr, pivot_index, j)){
                    i++; // increment index of smaller elements
                    SORT::UTILS::swap<T>(&arr[i], &arr[j]);
                }
            }
            // the i-th element is the last one that small than pivot, so swap the (i+1)-th　element with the pivot
            SORT::UTILS::swap<T>(&arr[i+1], &arr[pivot_index]);
            // (i+1) is position of the pivot
            return (i+1);
        }

        template<typename T>
        void quickSortKernel(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc){
            quickSortKernel(arr, 0, n-1, compFunc);
        }

        template<typename T>
        void quickSortKernel(T arr[], long low, long high, COMPARATOR::ARRAY::CompareFunc compFunc){
            if (low < high){
                // arr[pivot_index] is at the right place
                long pivot_index = partition(arr, low, high, compFunc);

                quickSortKernel(arr, low, pivot_index-1, compFunc);
                quickSortKernel(arr, pivot_index+1, high, compFunc);
            }
        }
    } //QUICK_SORT
} //SORT
