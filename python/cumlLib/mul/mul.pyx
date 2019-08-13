# distutils: language = c++

from cmul cimport mul

def pymul(a, b):
    return mul(a,b)


