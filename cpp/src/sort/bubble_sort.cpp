#include "bubble_sort.h"

namespace SORT{
    namespace BUBBLE_SORT{

        template<typename T>
        void bubbleSortKernel(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc){
            size_t i,j;
            bool swapped;
            for(i = 0; i < n; i++){
                swapped = false;
                for( j = 0; j < n-i-1; j++){
                    if(compFunc(arr, j, j+1)){
                        SORT::UTILS::swap<T>(&arr[j], &arr[j+1]);
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
            template void bubbleSortKernel<T>(T arr[], size_t n, COMPARATOR::ARRAY::CompareFunc compFunc);
        REGISTER_REAL_NUMBER_TYPES(DEFINE_SORT_KERNELS);
    } // BUBBLE_SORT
} //SORT


