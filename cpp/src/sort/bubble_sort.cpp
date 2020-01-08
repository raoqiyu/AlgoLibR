#include "bubble_sort.h"

namespace SORT{
    namespace BUBBLE_SORT{

        template<typename T>
        void bubbleSortKernel(T arr[], size_t n){
            size_t i,j;
            bool swapped;
            for(i = 0; i < n; i++){
                swapped = false;
                for( j = 0; j < n-i-1; j++){
                    if(arr[j] > arr[j+1]){
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
    } // BUBBLE_SORT
} //SORT


