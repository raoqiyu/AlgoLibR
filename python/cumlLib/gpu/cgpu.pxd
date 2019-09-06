cdef extern from "gpu/enum_gpu.cu":
    pass

cdef extern from "gpu/enum_gpu.h" namespace "GPU":
    int findGpu()
