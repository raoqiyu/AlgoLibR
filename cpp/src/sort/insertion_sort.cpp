#include "insertion_sort.h"

namespace SORT{
    namespace INSERTION_SORT{

        /*Maintain an sorted array a[0...i-1] and insert element a[i] into it
        Binary insertion sort use binary search to find the position to insert the key arr[i].
        In sequential insertion sort, it takes O(n) comparisions (at each iteration) in worest case.
        In Binary insertion sort, it takes O(log n) comparisions.
        */
        template<typename T>
        void binaryInsertionSortKernel(T arr[], long n, COMPARATOR::NUMBER::CompareFunc<T> compFunc){ // use long n, not size_t n (Segmentation fault)
            long i,j,pos;
            T key;
            for(i = 1; i < n; i++){
                key = arr[i];//the element to be inserted into the sorted array arr[0...i-1]
                // find the position where arr[i] will be in
                pos = SEARCH::BINARY_SEARCH::binarySearchKernel(arr, key, 0, i-1, compFunc);
                j = i-1;
                while(j >= pos ){
                    arr[j+1] = arr[j];
                    j--;
                }
                arr[j+1] = key;
            }
        }
        /*Maintain an sorted array a[0...i-1] and insert element a[i] into it
        */
        template<typename T>
        void sequentialInsertionSortKernel(T arr[], size_t n, COMPARATOR::NUMBER::CompareFunc<T> compFunc){
            long i,j;
            T key;
            for(i = 1; i < n; i++){
                key = arr[i];//the element to be inserted into the sorted array arr[0...i-1]
                // find the position where arr[i] will be in
                j = i-1;
                while( j >= 0 && compFunc(arr[j],key)){
                    arr[ j+1] = arr[j];
                    j--;
                }
                arr[j+1] = key;
            }
        }

        template<typename T>
        void insertionSortKernel(T arr[], size_t n, COMPARATOR::NUMBER::CompareFunc<T> compFunc){
            binaryInsertionSortKernel(arr, n, compFunc);
        }

        #define DEFINE_SORT_KERNELS(T) \
            template void insertionSortKernel<T>(T arr[], size_t n, COMPARATOR::NUMBER::CompareFunc<T> compFunc);
        REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);
    } //INSERTION_SORT
} //SORT


