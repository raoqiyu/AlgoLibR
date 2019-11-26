cdef extern from "sort/radix_sort.h" namespace "SORT::RADIX_SORT":
    void radix_sort_kernel(unsigned int*  h_inputVals, unsigned int* h_outputVals, const size_t numElems)
