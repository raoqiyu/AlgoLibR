cimport cython
from libcpp cimport bool


cdef extern from "data_structure/heap.h" namespace "DATA_STRUCTURE::HEAP":
    cdef cppclass HeapImp[T]:
        HeapImp(size_t capacity, bool is_max_heap)
        void insert(T data)
        void remove()
        T    get()
        size_t size()
        T*   values()
