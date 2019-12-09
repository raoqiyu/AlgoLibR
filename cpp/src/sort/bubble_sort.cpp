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

    template  void bubbleSortKernel<short>(short arr[], size_t n);
    template  void bubbleSortKernel<unsigned short>(unsigned short arr[], size_t n);

    template  void bubbleSortKernel<int>(int arr[], size_t n);
    template  void bubbleSortKernel<unsigned int>(unsigned int arr[], size_t n);

    template  void bubbleSortKernel<long>(long arr[], size_t n);
    template  void bubbleSortKernel<unsigned long>(unsigned long arr[], size_t n);

    template  void bubbleSortKernel<long long>(long long arr[], size_t n);
    template  void bubbleSortKernel<unsigned long long>(unsigned long long arr[], size_t n);

    template  void bubbleSortKernel<float>(float arr[], size_t n);

    template  void bubbleSortKernel<double>(double arr[], size_t n);
    }
}


