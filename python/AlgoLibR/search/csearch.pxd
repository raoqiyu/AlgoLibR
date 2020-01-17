cimport cython
from libcpp cimport bool

cdef extern from "search/utils.h" namespace "SEARCH":
    cdef enum SEARCH_METHOD:
        BINARY_SEARCH_M

cdef extern from "search/search.h" namespace "SEARCH":
    long long searchKernel[T](T arr[], T target, size_t n, SEARCH_METHOD method, bool ascending, bool isExist);