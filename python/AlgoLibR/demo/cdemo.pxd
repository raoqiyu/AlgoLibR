'''
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/python/AlgoLibR/demo/cdemo.pxd
Description: 
'''

from AlgoLibR.utils.string cimport wchar_t,wstring, to_wchar_t,to_wstring,from_wstring

cdef extern from "AlgoLibR/demo/mul.h" namespace "AlgoLibR::demo":
    int mul(int a, int b)

# Decalre the class with cdef
cdef extern from "AlgoLibR/demo/demo.h" namespace "AlgoLibR::demo":
    cdef cppclass MyDemo:
        MyDemo() except +
        MyDemo(int) except +
        int a
        int mul(int)
        int pymul(int)
        int add(int )
        void sayHello(wchar_t*)

