cimport cython

cdef extern from "sort/radix_sort.h" namespace "SORT::RADIX_SORT":
    void radix_sort_kernel(unsigned int*  h_inputVals, unsigned int* h_outputVals, const size_t numElems)


cdef extern from "sort/bubble_sort.h" namespace "SORT::BUBBLE_SORT":
    cdef void bubbleSortKernel[T](T *arr, int n)

cdef extern from "sort/quick_sort.h" namespace "SORT::QUICK_SORT":
    cdef void quickSortKernel[T](T *arr, long n)

cdef extern from "sort/selection_sort.h" namespace "SORT::SELECTION_SORT":
    cdef void selectionSortKernel[T](T *arr, unsigned int n)

cdef extern from "sort/insertion_sort.h" namespace "SORT::INSERTION_SORT":
    cdef void insertionSortKernel[T](T *arr, long n)

ctypedef fused real:
    cython.short
    cython.ushort
    cython.int
    cython.uint
    cython.long
    cython.ulong
    cython.longlong
    cython.ulonglong
    cython.float
    cython.double
