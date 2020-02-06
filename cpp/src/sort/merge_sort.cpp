/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-06 18:52:43
 * @FilePath: /AlgoLibR/cpp/src/sort/merge_sort.cpp
 * @Description: 
 */

#include "sort/merge_sort.h"
#include"utils/comparator.hpp"
#include "utils/register_types.h"


namespace SORT{
    namespace MERGE_SORT{
        
        /*Merger tow sorted subarrays of arr[]
        The first subarray is arr[low:middle]
        The second subarray is arr[middle+1:high]
        */
        template<typename T>
        void merge(T arr[], size_t low, size_t middle, size_t high, COMPARATOR::NUMBER::CompareFunc<T> compFunc){
            size_t i,j,k;

            // create tow temp arrays
            size_t left_size=middle-low+1, right_size=high-middle;
            T left[left_size], right[right_size];

            // copy two sorted subarrays to tmp arrays
            for(i = 0; i < left_size; i++){
                left[i] = arr[i+low];
            }
            for(i = 0; i < right_size; i++){
                right[i] = arr[i+middle+1];
            }

            // merge two temp arrays back into arr[low:high]
            i=0, j=0, k=low; // initialize array inedx, k start from low
            while(i < left_size && j < right_size){
                // stable sort: use less equal or greater equal
                if( compFunc(left[i], right[j]) ){
                    arr[k] = left[i++];
                }else{
                    arr[k] = right[j++];
                }
                k++;
            }
            while(i<left_size){
                arr[k++] = left[i++];
            }
            while(j<right_size){
                arr[k++] = right[j++];
            }
            return;
        }

        
        template<typename T>
        void mergeSortKernel(T arr[], size_t low, size_t high, COMPARATOR::NUMBER::CompareFunc<T> compFunc){
            if(low < high){
                size_t middle = low + (high-low)/2;

                mergeSortKernel(arr, low, middle, compFunc);
                mergeSortKernel(arr, middle+1, high, compFunc);

                merge(arr, low, middle, high, compFunc);
            }
        }


        template<typename T>
        void mergeSortKernel(T arr[], size_t low, size_t high, bool ascending){
            COMPARATOR::NUMBER::CompareFunc<T> compFunc = COMPARATOR::NUMBER::less_equal<T>; 
            if(ascending){
                compFunc = COMPARATOR::NUMBER::greater<T>;
            }
            mergeSortKernel(arr, low, high, compFunc);
            
        }
        
        template<typename T>
        void mergeSortKernel(T arr[], size_t n, bool ascending){
            if(n <= 0){
                return;
            }
            COMPARATOR::NUMBER::CompareFunc<T> compFunc = COMPARATOR::NUMBER::less_equal<T>; 
            if(ascending){
                compFunc = COMPARATOR::NUMBER::greater_equal<T>;
            }
            mergeSortKernel(arr, 0, n-1, compFunc);
        }


         #define DEFINE_SORT_KERNELS(T) \
            template void merge<T>(T arr[], size_t low, size_t middle, size_t high, COMPARATOR::NUMBER::CompareFunc<T> compFunc);  \
            template void mergeSortKernel<T>(T arr[], size_t low, size_t high, COMPARATOR::NUMBER::CompareFunc<T> compFunc);  \
            template void mergeSortKernel<T>(T arr[], size_t n, bool ascending);
        REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);

    } // MERGE_SORT
} // SORT
