cdef extern from "mul/mul.cpp":
    pass

cdef extern from "mul/mul.h" namespace "mul":
    int mul(int a, int b)
