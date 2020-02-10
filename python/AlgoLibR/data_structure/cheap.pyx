# distutils: language = c++
'''
Author: raoqiyu@gmail.com
Date: 2020-02-06 18:37:54
FilePath: /AlgoLibR/python/AlgoLibR/data_structure/cheap.pyx
Description: 
'''

# distutils: language = c++
'''
Author: raoqiyu@gmail.com
Date: 2020-02-06 18:37:54
FilePath: /AlgoLibR/python/AlgoLibR/data_structure/heap.pyx
Description: 
'''

cimport cython
from libcpp cimport bool
from cdata_structure cimport insert_heap, remove_heap, get_heap
from AlgoLibR.utils.data_types cimport real_number
from AlgoLibR.utils.memory import malloc_memory
import numpy as np

def insert(real_number[:] arr, real_number data, size_t n, size_t heap_size, bool is_max_heap):
    return  insert_heap(&arr[0], data, n, heap_size, is_max_heap)

def remove(real_number[:] arr, size_t n, size_t heap_size, bool is_max_heap):
    return remove_heap(&arr[0], n, heap_size, is_max_heap)

def get(real_number[:] arr, size_t heap_size):
    return get_heap(&arr[0], heap_size)

class Heap:
    def __init__(self, capacity=100, is_max_heap=True, dtype=np.int32):
        self.dtype = dtype
        self.__arr = malloc_memory(capacity, dtype)
        self.__heap_size = 0
        self.__capacity = capacity
        self.__is_max_heap = is_max_heap

    def insert(self, data):
        is_inserted = insert(self.arr, data, self.capacity, self.heap_size, self.is_max_heap)
        if is_inserted:
            self.__heap_size += 1

    def remove(self):
        if self.__heap_size == 0:
            return
        is_removed = remove(self.arr, self.capacity, self.heap_size, self.is_max_heap)
        if is_removed:
            self.__heap_size -= 1
    
    def get(self):
        return get(self.arr, self.heap_size)

    def size(self):
        return self.__heap_size
    
    def values(self):
        return self.__arr[:self.__heap_size]