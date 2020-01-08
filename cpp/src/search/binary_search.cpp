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

	} // end of namespace  BINARY_SEARCH
}// end of namespace  SEARCH