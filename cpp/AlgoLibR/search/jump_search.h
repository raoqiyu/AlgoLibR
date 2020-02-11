/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-11 14:19:29
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/search/jump_search.h
 * @Description: 
 */

#ifndef JUMP_SERCH_H
#define JUMP_SERCH_H

#include <stdlib.h>

namespace AlgoLibR{
namespace search{
namespace jump_search{

    template<typename T>
    long long jumpSearchKernel(T arr[], T target, size_t n, bool ascending);

} // namespace jump_search
} // namespace search
} // namespace AlgoLibR

#endif
