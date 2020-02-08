# distutils: language = c++
'''
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/python/AlgoLibR/device/gpu/enum_gpu.pyx
Description: 
'''

from cgpu cimport findGpu

def enum_gpu_info():
    return findGpu()
