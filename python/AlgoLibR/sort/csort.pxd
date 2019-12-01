cimport cython

cdef extern from "sort/radix_sort.h" namespace "SORT::RADIX_SORT":
    void radix_sort_kernel(unsigned int*  h_inputVals, unsigned int* h_outputVals, const size_t numElems)


cdef extern from "sort/bubble_sort.h" namespace "SORT::BUBBLE_SORT":
    cdef void bubbleSortKernel[T](T *arr, int n)

