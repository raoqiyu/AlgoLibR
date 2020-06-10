import cython
cimport cython
from csort_gpu cimport radix_sort_kernel

def radix_sort(nums):
    nums = py_data_to_c_data(nums,dtype=np.uint32, copy=False)
    out = malloc_memory_from_data(nums,copy=False)

    cdef cython.uint[:] nums_memview = nums
    cdef cython.uint[:] out_memview = out

    radix_sort_kernel(&nums_memview[0], &out_memview[0], len(nums))

    return out
