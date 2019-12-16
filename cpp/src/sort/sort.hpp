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
    void sortKernel(T arr[], size_t n, enum SORT_METHOD method){
        if(n == 0){
            return ;
        }

        switch(method){
            case BUBBLE_SORT_M:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n);
                break;
            case INSERTION_SORT_M:
                SORT::INSERTION_SORT::insertionSortKernel(arr, n);
                break;
            case QUICK_SORT_M:
                SORT::QUICK_SORT::quickSortKernel(arr, n);
                break;
            case SELECTION_SORT_M:
                SORT::SELECTION_SORT::selectionSortKernel(arr, n);
                break;
            default:
                SORT::BUBBLE_SORT::bubbleSortKernel(arr, n);
        };

    }

}
#endif