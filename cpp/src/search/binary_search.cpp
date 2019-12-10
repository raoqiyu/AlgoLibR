#include "binary_search.h"

namespace SEARCH{
    namespace BINARY_SEARCH{

    template<typename T>
    size_t binarySearchKernel(T arr[], T target, long low, long high){
        if(low > high){
            return (target > arr[low]) ? low+1:low;
        }
        long mid = low + (high-low)/2;

        if(target == arr[mid]){
            return mid;
        } else if(target > arr[mid]){
            return binarySearchKernel(arr, target, mid+1, high);
        } else {
            return binarySearchKernel(arr, target, low, mid-1);
        }
    }


    template  size_t binarySearchKernel<short>(short arr[], short target, long low, long high);
    template  size_t binarySearchKernel<unsigned short>(unsigned short arr[], unsigned short target, long low, long high);

    template  size_t binarySearchKernel<int>(int arr[], int target, long low, long high);
    template  size_t binarySearchKernel<unsigned int>(unsigned int arr[], unsigned int target, long low, long high);

    template  size_t binarySearchKernel<long>(long arr[], long target, long low, long high);
    template  size_t binarySearchKernel<unsigned long>(unsigned long arr[], unsigned long target, long low, long high);

    template  size_t binarySearchKernel<long long>(long long arr[], long long target, long low, long high);
    template  size_t binarySearchKernel<unsigned long long>(unsigned long long arr[], unsigned long long target, long low, long high);

    template  size_t binarySearchKernel<float>(float arr[], float target, long low, long high);

    template  size_t binarySearchKernel<double>(double arr[], double target, long low, long high);

	} // end of namespace  BINARY_SEARCH
}// end of namespace  SEARCH