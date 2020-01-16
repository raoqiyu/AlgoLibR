#include "binary_search.h"

namespace SEARCH{
    namespace BINARY_SEARCH{

    template<typename T>
    size_t binarySearchKernel(T arr[], T target, long low, long high, COMPARATOR::NUMBER::CompareFunc<T> compFunc){
        if(low > high){
            return (compFunc(target, arr[low])) ? low+1:low;
        }
        long mid = low + (high-low)/2;

        if(target == arr[mid]){
            return mid;
        } else if(compFunc(target,arr[mid])){
            return binarySearchKernel(arr, target, mid+1, high, compFunc);
        } else {
            return binarySearchKernel(arr, target, low, mid-1, compFunc);
        }
    }
    
    
    #define DEFINE_SEARCH_KERNELS(T) \
        template size_t binarySearchKernel<T>(T arr[], T target, long low, long high, COMPARATOR::NUMBER::CompareFunc<T> compFunc);
    REGISTER_REAL_NUMBER_TYPES(DEFINE_SEARCH_KERNELS);

	} // end of namespace  BINARY_SEARCH
}// end of namespace  SEARCH