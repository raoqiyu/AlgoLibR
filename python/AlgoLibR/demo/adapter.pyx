# distutils: language = c++
'''
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/python/AlgoLibR/demo/adapter.pyx
Description: 
'''

from cdemo cimport MyDemo
from AlgoLibR.utils.string cimport wchar_t,wstring, to_wchar_t,to_wstring,from_wstring

# Create a Cython extension type which holds a C++ instance
# as an attribute and create a bunch of forwarding methods
# Python extension type.
cdef class PyMyDemo:
    cdef MyDemo c_mydemo  # Hold a C++ instance which we're wrapping

    def __cinit__(self,a):
        self.c_mydemo = MyDemo(a)   

    def mul(self, m):
        return self.c_mydemo.mul(m)

    def pymul(self, m):
        return self.c_mydemo.pymul(m)

    def add(self,b):
        return self.c_mydemo.add(b)

        self.c_mydemo.sayHello(name)
    
    def sayHello(self, name):
        cdef wchar_t* s = to_wchar_t(name)
        self.c_mydemo.sayHello(s)


