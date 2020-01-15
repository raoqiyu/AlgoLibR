/*
@Author: raoqiyu@gmail.com
@Time: 2019-12-13 17:10:09
@File: sort.h
*/
#ifndef SORT_H
#define SORT_H

#include "bubble_sort.h"
#include "insertion_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"

namespace SORT{

    template<typename T>
    void sortKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending){
        if(n == 0){
            return ;
        }
        COMPARATOR::ARRAY::CompareFunc compFunc = COMPARATOR::ARRAY::less<T>;
        if(ascending){
            compFunc = COMPARATOR::ARRAY::greater<T>;
        }

        switch(method){
            case BUBBLE_SORT_M:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n, compFunc);
                break;
            case QUICK_SORT_M:
                SORT::QUICK_SORT::quickSortKernel(arr, n, compFunc);
                break;
            case SELECTION_SORT_M:
                SORT::SELECTION_SORT::selectionSortKernel(arr, n, compFunc);
                break;
            case INSERTION_SORT_M:
                COMPARATOR::NUMBER::CompareFunc<T> compFuncNum;
                if(ascending){
                    compFuncNum = COMPARATOR::NUMBER::greater<T>;
                }else{
                    compFuncNum = COMPARATOR::NUMBER::less<T>;
                }
                SORT::INSERTION_SORT::insertionSortKernel(arr, n, compFuncNum);
                break;
            default:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n, compFunc);
        };

    }

} //SORT
#endif