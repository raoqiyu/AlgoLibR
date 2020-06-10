'''
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/python/AlgoLibR/sort/csort.pxd
Description: 
'''

cimport cython
from libcpp cimport bool
from AlgoLibR import use_gpu



cdef extern from "AlgoLibR/sort/utils.h" namespace "AlgoLibR::sort":
    cdef enum SORT_METHOD:
        BUBBLE_SORT_M,
        INSERTION_SORT_M,
        QUICK_SORT_M,
        SELECTION_SORT_M,
        COUNT_SORT_M,
        RADIX_SORT_M,
        HEAP_SORT_M,
        MERGE_SORT_M,
        TIM_SORT_M

cdef extern from "AlgoLibR/sort/sort.h" namespace "AlgoLibR::sort":
    cdef void sortKernel[T](T *arr, size_t n, SORT_METHOD method, bool ascending)
    cdef void sortIntegerKernel[T](T *arr, size_t n, SORT_METHOD method, bool ascending)