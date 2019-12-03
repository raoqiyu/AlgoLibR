# distutils: language = c++
import cython
cimport cython
import numpy as np
from cpython cimport array
from csort cimport real
from csort cimport radix_sort_kernel,bubbleSortKernel
from AlgoLibR.utils.memory import py_data_to_c_data,malloc_memory_from_data



def radix_sort(nums):
    nums = py_data_to_c_data(nums,dtype=np.uint32, copy=False)
    out = malloc_memory_from_data(nums,copy=False)

    cdef cython.uint[:] nums_memview = nums
    cdef cython.uint[:] out_memview = out

    radix_sort_kernel(&nums_memview[0], &out_memview[0], len(nums))

    return out

def bubble_sort(real[:] nums):
    bubbleSortKernel(&nums[0], nums.shape[0])
    return

def sort(nums, method=None):
    """
    :param nums:
    :param method: one of [radix, None], when method is None, use python's default `sorted` method
    :return:
    """
    if method is None:
        return sorted(nums)
    elif method == 'radix':
        return radix_sort(nums)
    elif method == 'bubble':
        nums = py_data_to_c_data(nums,copy=False)
        bubble_sort(nums)
        return nums
    else:
        raise Exception('Method %s not supported yet'%method)
