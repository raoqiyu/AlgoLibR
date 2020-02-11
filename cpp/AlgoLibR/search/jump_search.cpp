/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-11 14:22:02
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/search/jump_search.cpp
 * @Description: 
 */

#include <math.h>
#include "AlgoLibR/search/jump_search.h"
#include "AlgoLibR/framework/comparator.hpp"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace search{
namespace jump_search{
/*Split array into subarrays, then jump to the subarray where target is in, then use linear search
The array should be sorted;
*/
template<typename T>
long long jumpSearchKernel(T arr[], T target, size_t n, bool ascending){
    if(n == 1){
        if(arr[0] == target){
            return 0;
        }else{
            return -1;
        }
    }

    comparator::number::CompareFunc<T> compFunc;
    if(ascending){
        compFunc = comparator::number::less<T>;
    }else{
        compFunc = comparator::number::greater<T>;
    }
    
    // check if target exist in arr
    if(compFunc(target,arr[0]) || compFunc(arr[n-1], target)){
            return -1;
    }

    // subarray size
    size_t split_size = sqrt(n);
    size_t split_index = 1;

    // jump the subarray where target is in
    while(compFunc(arr[comparator::number::min(split_index * split_size, n)-1], target)){
        
        if(split_index*split_size >= n){
            return -1;
        }
        split_index += 1;
    }

    // linear serach the target subarray
    size_t begin_idx = (split_index-1)*split_size;
    size_t end_idx = comparator::number::min(split_index*split_size, n);
    while(compFunc(arr[begin_idx], target)){
        begin_idx++;
        if(begin_idx == end_idx ){
            return -1;
        }
    }

    if(target == arr[begin_idx]){
        return begin_idx;
    }

    return -1;
}


#define DEFINE_SEARCH_KERNELS(T) \
    template long long jumpSearchKernel<T>(T arr[], T target, size_t n, bool ascending);
REGISTER_REAL_NUMBER_TYPES(DEFINE_SEARCH_KERNELS);

} // namespace jump_search
} // namespace search
} // namespace AlgoLibR