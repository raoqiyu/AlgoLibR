cdef extern from "sort/sort.h" namespace "SORT":
    void radix_sort(unsigned int*  h_inputVals, unsigned int* h_outputVals, const size_t numElems)
