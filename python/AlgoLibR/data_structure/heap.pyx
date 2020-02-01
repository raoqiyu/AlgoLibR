# distutils: language = c++
cimport cython
from cdata_structure cimport HeapImp
from AlgoLibR.utils.data_types cimport real_number

cdef class Heap:
    cdef HeapImp[cython.int] *c_heap

    def __cinit__(self, capacity=100, is_max_heap=True):
        self.c_heap = new HeapImp[cython.int](capacity, is_max_heap)

    def insert(self, data):
        self.c_heap.insert(data)

    def remove(self):
        self.c_heap.remove()
    
    def get(self):
        return self.c_heap.get()
    
    def size(self):
        return self.c_heap.size()
