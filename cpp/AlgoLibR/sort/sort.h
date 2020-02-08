/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-31 20:03:29
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/sort.h
 * @Description: 
 */

#ifndef SORT_H
#define SORT_H

#include "AlgoLibR/sort/utils.h"

namespace AlgoLibR{
namespace sort{

template<typename T>
void sortKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending);

template<typename T>
void sortIntegerKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending);

} // namespace sort
} // namespace AlgoLibR

#endif
