'''
Author: raoqiyu@gmail.com
Date: 2020-01-17 09:27:14
FilePath: /AlgoLibR/python/AlgoLibR/utils/data_types.pxd
Description: 
'''

cimport cython

ctypedef fused integer_number:
    cython.short
    cython.ushort
    cython.int
    cython.uint
    cython.long
    cython.ulong
    cython.longlong
    cython.ulonglong

ctypedef fused real_number:
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