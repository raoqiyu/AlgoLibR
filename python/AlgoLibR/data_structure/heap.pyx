# distutils: language = c++
cimport cython
from cdata_structure cimport HeapImp
from AlgoLibR.utils.data_types cimport real_number

cdef class Heap:
    cdef HeapImp[cython.uint] *c_heap_uint
    cdef HeapImp[cython.int] *c_heap_int
    cdef HeapImp[cython.ulong] *c_heap_ulong
    cdef HeapImp[cython.long] *c_heap_long
    cdef HeapImp[cython.float] *c_heap_float
    cdef HeapImp[cython.double] *c_heap_double
    cdef str dtype

    def __cinit__(self, capacity=100, is_max_heap=True, dtype='int'):
        self.dtype = dtype
        if self.dtype == 'int':
            self.c_heap_int = new HeapImp[cython.int](capacity, is_max_heap)
        elif self.dtype == 'uint':
            self.c_heap_uint = new HeapImp[cython.uint](capacity, is_max_heap)
        elif self.dtype == 'long':
            self.c_heap_long = new HeapImp[cython.long](capacity, is_max_heap)
        elif self.dtype == 'ulong':
            self.c_heap_ulong = new HeapImp[cython.ulong](capacity, is_max_heap)
        elif self.dtype == 'float':
            self.c_heap_float= new HeapImp[cython.float](capacity, is_max_heap)
        else:
            self.c_heap_double= new HeapImp[cython.double](capacity, is_max_heap)

    def insert(self, data):
        if self.dtype == 'int':
            self.c_heap_int.insert(data)
        elif self.dtype == 'uint':
            self.c_heap_uint.insert(data)
        elif self.dtype == 'long':
            self.c_heap_long.insert(data)
        elif self.dtype == 'ulong':
            self.c_heap_ulong.insert(data)
        elif self.dtype == 'float':
            self.c_heap_float.insert(data)
        else:
            self.c_heap_double.insert(data)

    def remove(self):
        if self.dtype == 'int':
            self.c_heap_int.remove()
        elif self.dtype == 'uint':
            self.c_heap_uint.remove()
        elif self.dtype == 'long':
            self.c_heap_long.remove()
        elif self.dtype == 'ulong':
            self.c_heap_ulong.remove()
        elif self.dtype == 'float':
            self.c_heap_float.remove()
        else:
            self.c_heap_double.remove()
    
    def get(self):
        if self.dtype == 'int':
            return self.c_heap_int.get()
        elif self.dtype == 'uint':
            return self.c_heap_uint.get()
        elif self.dtype == 'long':
            return self.c_heap_long.get()
        elif self.dtype == 'ulong':
            return self.c_heap_ulong.get()
        elif self.dtype == 'float':
            return self.c_heap_float.get()
        else:
            return self.c_heap_double.get()

    def size(self):
        if self.dtype == 'int':
            self.c_heap_int.size()
        elif self.dtype == 'uint':
            self.c_heap_uint.size()
        elif self.dtype == 'long':
            self.c_heap_long.size()
        elif self.dtype == 'ulong':
            self.c_heap_ulong.size()
        elif self.dtype == 'float':
            self.c_heap_float.size()
        else:
            self.c_heap_double.size()
    """
    def values(self):
        py_vals = []
        if self.dtype == 'int':
            vals = self.c_heap_int.values()
            for i in range(self.size()):
                py_vals.append(vals[i])
        elif self.dtype == 'uint':
            vals = self.c_heap_uint.values()
            for i in range(self.size()):
                py_vals.append(vals[i])
        elif self.dtype == 'long':
            vals = self.c_heap_long.values()
            for i in range(self.size()):
                py_vals.append(vals[i])
        elif self.dtype == 'ulong':
            vals = self.c_heap_ulong.values()
            for i in range(self.size()):
                py_vals.append(vals[i])
        elif self.dtype == 'float':
            vals = self.c_heap_float.values()
            for i in range(self.size()):
                py_vals.append(vals[i])
        else:
            vals = self.c_heap_double.values()
            for i in range(self.size()):
                py_vals.append(vals[i])
        return py_vals
        """

    def __dealloc__(self):
        if self.dtype == 'int':
            del self.c_heap_int
        elif self.dtype == 'uint':
            del self.c_heap_uint
        elif self.dtype == 'long':
            del self.c_heap_long
        elif self.dtype == 'ulong':
            del self.c_heap_ulong
        elif self.dtype == 'float':
            del self.c_heap_float
        else:
            del self.c_heap_double