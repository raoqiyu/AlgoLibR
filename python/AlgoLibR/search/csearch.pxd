cimport cython
from libcpp cimport bool

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

cdef extern from "search/utils.h" namespace "SEARCH":
    cdef enum SEARCH_METHOD:
        BINARY_SEARCH_M

cdef extern from "search/search.h" namespace "SEARCH":
    long long searchKernel[T](T arr[], T target, size_t n, SEARCH_METHOD method, bool ascending, bool isExist);