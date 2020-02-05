cimport cython
from libcpp cimport bool


cdef extern from "data_structure/heap.h" namespace "DATA_STRUCTURE::HEAP":
        cdef bool insert_heap[T](T arr[], T data, size_t n, size_t heap_size, bool is_max_heap)
        cdef bool remove_heap[T](T arr[], size_t n, size_t heap_size, bool is_max_heap)
        cdef T    get_heap[T](T arr[], size_t heap_size)