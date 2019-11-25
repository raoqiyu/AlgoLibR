cdef extern from "mul/mul.cpp":
    pass
cdef extern from "mul/mul.h" namespace "mul":
    int mul(int a, int b)

cdef extern from "demo/demo.cpp":
    pass

# Decalre the class with cdef
cdef extern from "demo/demo.h" namespace "demo":
    cdef cppclass MyDemo:
        MyDemo() except +
        MyDemo(int) except +
        int a
        int mul(int)
        int pymul(int)
        int add(int )
        void sayHello(char*)

