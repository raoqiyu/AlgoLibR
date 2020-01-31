/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 14:09:24
 * @FilePath: /AlgoLibR/cpp/src/sort/count_sort.cpp
 * @Description: 
 */

#include<string.h> 
#include "sort/count_sort.h"

namespace SORT{
    namespace COUNT_SORT{

        template<typename T>
        void countSortKernel(T arr[],size_t n, bool ascending){
            T output_arr[n];
            T max_ele = ARRAY::COMPARE::max(arr, n);
            T min_ele = ARRAY::COMPARE::min(arr, n);
            T count[max_ele - min_ele + 1];
            memset(count, 0, sizeof(count));  

            for(auto i = 0; i < n; i++){
                count[arr[i]-min_ele] += 1;
            }
            // change the count, now count sotres the actural position of the number
            for(auto i = 1; i < (max_ele-min_ele+1); i++){
                count[i] += count[i-1];
            }
            int count_idx;
            // reverse-order traversal is for the stability
            for(long long i = n-1; i >= 0; i--){
                count_idx = arr[i] - min_ele;
                output_arr[count[count_idx]-1] = arr[i];
                count[count_idx] -= 1;
            }
            if(ascending){
                for(auto i = 0; i < n; i++){
                    arr[i] = output_arr[i];
                }
            }else{
                for(auto i = 0; i < n; i++){
                    arr[i] = output_arr[n-i-1];
                }
            }
        }

        template<typename T>
        void radixCountSortKernel(T arr[], size_t n, int exp, bool ascending){
            T output_arr[n];
            int radix_count[10] = {0};
            // store the count of 
            // store the count of 
            for(auto i=0; i < n; i++){
                radix_count[(arr[i]/exp)%10]++;
            }
            // change the radix_count, now radix_count sotres the actural position of the digit
            for(auto i = 1; i < 10; i++){
                radix_count[i] += radix_count[i-1];
            }
            int count_idx;
            // reverse-order traversal is for the stability
            for(long long i = n-1; i >= 0; i--){
                count_idx = (arr[i]/exp)%10;
                output_arr[radix_count[count_idx]-1] = arr[i];
                radix_count[count_idx] -= 1;
            }
            if(ascending){
                for(auto i = 0; i < n; i++){
                    arr[i] = output_arr[i];
                }
            }else{
                for(auto i = 0; i < n; i++){
                    arr[i] = output_arr[n-i-1];
                }
            }
        }
        
        #define DEFINE_SORT_KERNELS(T) \
            template void countSortKernel<T>(T arr[], size_t n, bool ascending); \
            template void radixCountSortKernel<T>(T arr[], size_t n, int exp, bool ascending);
        REGISTER_INTEGER_TYPES(DEFINE_SORT_KERNELS);
    } // COMPARATOR
} //SORT