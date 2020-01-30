cimport cython
from libcpp cimport bool


cdef extern from "sort/radix_sort.h" namespace "SORT::RADIX_SORT":
    void radix_sort_kernel(unsigned int*  h_inputVals, unsigned int* h_outputVals, const size_t numElems)


cdef extern from "sort/utils.h" namespace "SORT":
    cdef enum SORT_METHOD:
        BUBBLE_SORT_M,
        INSERTION_SORT_M,
        QUICK_SORT_M,
        SELECTION_SORT_M,
        COUNT_SORT_M,
        RADIX_SORT_M

cdef extern from "sort/sort.hpp" namespace "SORT":
    cdef void sortKernel[T](T *arr, size_t n, SORT_METHOD method, bool ascending)
    cdef void sortIntegerKernel[T](T *arr, size_t n, SORT_METHOD method, bool ascending)