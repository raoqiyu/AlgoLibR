# distutils: language = c++

from cgpu cimport findGpu

def enum_gpu_info():
    return findGpu()
