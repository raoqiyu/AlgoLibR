/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-14 14:38:30
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/bubble_sort.cpp
 * @Description: 
 */

#include "AlgoLibR/sort/bubble_sort.h"

namespace AlgoLibR{
namespace sort{
namespace bubble_sort{

template<typename T>
void bubbleSortKernel(T arr[], size_t n, comparator::array::CompareFunc compFunc){
    size_t i,j;
    bool swapped;
    for(i = 0; i < n; i++){
        swapped = false;
        for( j = 0; j < n-i-1; j++){
            if(compFunc(arr, j, j+1)){
                sort::UTILS::swap<T>(&arr[j], &arr[j+1]);
                swapped = true;
            }
        }
        // optimized : stop if inner loop does not cause any swap ( the array is sorted)
        if(swapped == false){
            break;
        }
    }
}

#define DEFINE_SORT_KERNELS(T) \
    template void bubbleSortKernel<T>(T arr[], size_t n, comparator::array::CompareFunc compFunc);
REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);

} // namespace bubble_sort
} // namespace sort
} // namespace AlgoLibR


