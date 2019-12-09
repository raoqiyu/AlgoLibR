#include "quick_sort.h"

namespace SORT{
    namespace QUICK_SORT{

        /*This function take the last element as pivot, places the pivot element at its correct position in sorted
        array, and places all smaller (small than pivot) to the left of pivot and all greater elements to the right.
        */
        template<typename T>
        long partition(T arr[], long low, long high){
            T pivot = arr[high]; // pivot
            long i = low-1; //index of the smaller elements
            for( auto j = low; j < high; j++){
                // if current element is small than the pivot
                if(arr[j] < pivot){
                    i++; // increment index of smaller elements
                    SORT::UTILS::swap<T>(&arr[i], &arr[j]);
                }
            }
            // the i-th element is the last one that small than pivot, so swap the (i+1)-th　element with the pivot
            SORT::UTILS::swap<T>(&arr[i+1], &arr[high]);
            // (i+1) is position of the pivot
            return (i+1);
        }

        template<typename T>
        void quickSortKernel(T arr[], size_t n){
            quickSortKernel(arr, 0, n-1);
        }

        template<typename T>
        void quickSortKernel(T arr[], long low, long high){
            if (low < high){
                // arr[pivot_index] is at the right place
                long pivot_index = partition(arr, low, high);

                quickSortKernel(arr, low, pivot_index-1);
                quickSortKernel(arr, pivot_index+1, high);
            }
        }


        template  void quickSortKernel<short>(short arr[], size_t n);
        template  void quickSortKernel<unsigned short>(unsigned short arr[], size_t n);

        template  void quickSortKernel<int>(int arr[], size_t n);
        template  void quickSortKernel<unsigned int>(unsigned int arr[], size_t n);

        template  void quickSortKernel<long>(long arr[], size_t n);
        template  void quickSortKernel<unsigned long>(unsigned long arr[], size_t n);

        template  void quickSortKernel<long long>(long long arr[], size_t n);
        template  void quickSortKernel<unsigned long long>(unsigned long long arr[], size_t n);

        template  void quickSortKernel<float>(float arr[], size_t n);
        template  void quickSortKernel<double>(double arr[], size_t n);
    }
}
