'''
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/python/AlgoLibR/device/gpu/cgpu.pxd
Description: 
'''

cdef extern from "AlgoLibR/device/gpu/enum_gpu.h" namespace "AlgoLibR::device::gpu":
    int findGpu()
