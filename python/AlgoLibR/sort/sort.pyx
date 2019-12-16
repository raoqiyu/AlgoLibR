# distutils: language = c++
import cython
cimport cython
import numpy as np
from csort cimport real,SORT_METHOD
from csort cimport radix_sort_kernel,sortKernel
from AlgoLibR.utils.memory import py_data_to_c_data,malloc_memory_from_data

sort_methods = {'insertion':SORT_METHOD.INSERTION_SORT_M,
                'bubble':SORT_METHOD.BUBBLE_SORT_M,
                'quick':SORT_METHOD.QUICK_SORT_M,
                'selection':SORT_METHOD.SELECTION_SORT_M,}


def radix_sort(nums):
    nums = py_data_to_c_data(nums,dtype=np.uint32, copy=False)
    out = malloc_memory_from_data(nums,copy=False)

    cdef cython.uint[:] nums_memview = nums
    cdef cython.uint[:] out_memview = out

    radix_sort_kernel(&nums_memview[0], &out_memview[0], len(nums))

    return out

# do not use cpdef : (Invalid use of fused types, type cannot be specialized)
def sort_kernel(real[:] nums, method):
    cdef size_t n_samples = nums.shape[0]

    sortKernel(&nums[0], n_samples, sort_methods[method])
    return

def sort(nums, method=None):
    """
    :param nums: array of np.ndarray. if nums is a list, will create a new np.ndarray from it.
    :param method: one of [radix, bubble, insertion, quick, selection], when method is None, use python's default `sorted` method
    :return:
    """
    if method is None:
        return sorted(nums)
    elif method == 'radix':
        return radix_sort(nums)
    elif method not in sort_methods:
        raise Exception('Unsupported method')
    else:
        nums = py_data_to_c_data(nums,copy=False)
        sort_kernel(nums, method)
        return nums