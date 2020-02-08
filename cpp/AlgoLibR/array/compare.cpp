/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-30 14:18:27
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/array/compare.cpp
 * @Description: 
 */

#include "AlgoLibR/array/compare.h"
#include "AlgoLibR/framework/register_types.h"

namespace AlgoLibR{
namespace array{
namespace COMPARE{
template<typename T>
T max(T arr[], size_t n){
    if(n < 0){
        return 0;
    }
    T target = arr[0];
    for(auto i = 1; i < n; i++){
        if(arr[i] > target){
            target = arr[i];
        }
    } // for
    return target;
}
template<typename T>
T min(T arr[], size_t n){
    if(n < 0){
        return 0;
    }
    T target = arr[0];
    for(auto i = 1; i < n; i++){
        if(arr[i] < target){
            target = arr[i];
        }
    } // for
    return target;
}
#define DEFINE_COMPARE_KERNELS(T) \
    template T max<T>(T arr[], size_t n); \
    template T min<T>(T arr[], size_t n);
REGISTER_REAL_NUMBER_TYPES(DEFINE_COMPARE_KERNELS);
} // namespace COMPARE
} // namespace array
} // namespace AlgoLibR

