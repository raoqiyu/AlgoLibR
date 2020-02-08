/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-16 10:47:00
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/search/search.hpp
 * @Description: 
 */

#include "AlgoLibR/search/utils.h"
#include "AlgoLibR/search/binary_search.h"

namespace AlgoLibR{
namespace search{

template<typename T>
long long searchKernel(T arr[], T target, size_t n, enum SEARCH_METHOD method, bool ascending, bool isExist){
    if(n == 0){
        return -1;
    }
    
    long long find_position;

    comparator::number::CompareFunc<T> compFunc = comparator::number::less<T>;
    if(ascending){
        compFunc = comparator::number::greater<T>;
    }

    switch(method){
        case BINARY_SEARCH_M:
            find_position = search::binary_search::binarySearchKernel(arr, target, n, isExist, compFunc);
            break;
        default:
            find_position = search::binary_search::binarySearchKernel(arr, target, n, isExist, compFunc);
            break; 
    }; // switch

    return find_position;
}

#define DEFINE_SEARCH_KERNELS(T) \
    template long long searchKernel<T>(T arr[], T target, size_t n, enum SEARCH_METHOD method, bool ascending, bool isExist);
REGISTER_REAL_NUMBER_TYPES(DEFINE_SEARCH_KERNELS);

} // namespace search
} // namespace AlgoLibR
