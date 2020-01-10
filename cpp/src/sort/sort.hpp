/*
@Author: raoqiyu@gmail.com
@Time: 2019-12-13 17:10:09
@File: sort.h
*/
#ifndef SORT_H
#define SORT_H

#include "sort_kernel_imp.h"

namespace SORT{

    template<typename T>
    void sortKernel(T arr[], size_t n, enum SORT_METHOD method, bool ascending){
        if(n == 0){
            return ;
        }
        SORT::UTILS::CompareFunc compFunc = SORT::UTILS::less<T>;
        if(ascending){
            compFunc = SORT::UTILS::greater<T>;
        }

        switch(method){
            case BUBBLE_SORT_M:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n, compFunc);
                break;
            case INSERTION_SORT_M:
                SORT::INSERTION_SORT::insertionSortKernel(arr, n);
                break;
            case QUICK_SORT_M:
                SORT::QUICK_SORT::quickSortKernel(arr, n);
                break;
            case SELECTION_SORT_M:
                SORT::SELECTION_SORT::selectionSortKernel(arr, n, compFunc);
                break;
            default:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n, compFunc);
        };

    }

} //SORT
#endif