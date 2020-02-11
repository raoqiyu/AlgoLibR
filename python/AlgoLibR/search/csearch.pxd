'''
Author: raoqiyu@gmail.com
Date: 2020-01-16 11:31:53
FilePath: /AlgoLibR/python/AlgoLibR/search/csearch.pxd
Description: 
'''

cimport cython
from libcpp cimport bool

cdef extern from "AlgoLibR/search/utils.h" namespace "AlgoLibR::search":
    cdef enum SEARCH_METHOD:
        BINARY_SEARCH_M
        JUMP_SEARCH_M

cdef extern from "AlgoLibR/search/search.h" namespace "AlgoLibR::search":
    long long searchKernel[T](T arr[], T target, size_t n, SEARCH_METHOD method, bool ascending, bool isExist);