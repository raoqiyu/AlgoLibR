# distutils: language = c++

from cpython cimport array
from csort cimport radix_sort

def sort(nums):
    cdef size_t n_samples = len(nums)

    cdef array.array h_in = array.array('I',nums)
    cdef array.array h_out = array.array('I')
    cdef unsigned int[:] h_out_py = h_out


    radix_sort(h_in.data.as_uints, h_out.data.as_uints, n_samples)

    del h_in
    return h_out_py
    # return nums_sorted