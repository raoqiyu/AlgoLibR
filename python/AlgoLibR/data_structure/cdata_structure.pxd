'''
Author: raoqiyu@gmail.com
Date: 2020-02-06 18:37:54
FilePath: /AlgoLibR/python/AlgoLibR/data_structure/cdata_structure.pxd
Description: 
'''

cimport cython
from libcpp cimport bool


cdef extern from "AlgoLibR/data_structure/heap.h" namespace "AlgoLibR::data_structure::heap":
        cdef bool insert_heap[T](T arr[], T data, size_t n, size_t heap_size, bool is_max_heap)
        cdef bool remove_heap[T](T arr[], size_t n, size_t heap_size, bool is_max_heap)
        cdef T    get_heap[T](T arr[], size_t heap_size)