# distutils: language = c++
import cython
cimport cython
import numpy as np
from cpython cimport array
from csort cimport real
from csort cimport radix_sort_kernel,bubbleSortKernel,quickSortKernel,selectionSortKernel,insertionSortKernel
from AlgoLibR.utils.memory import py_data_to_c_data,malloc_memory_from_data


def radix_sort(nums):
    nums = py_data_to_c_data(nums,dtype=np.uint32, copy=False)
    out = malloc_memory_from_data(nums,copy=False)

    cdef cython.uint[:] nums_memview = nums
    cdef cython.uint[:] out_memview = out

    radix_sort_kernel(&nums_memview[0], &out_memview[0], len(nums))

    return out

# do not use cpdef : (Invalid use of fused types, type cannot be specialized)
def sort_kernel(real[:] nums, method='bubble'):
    cdef size_t n_samples = nums.shape[0]

    if method == 'bubble':
        bubbleSortKernel(&nums[0], n_samples)
    elif method == 'quick':
        quickSortKernel(&nums[0], n_samples)
    elif method == 'selection':
        selectionSortKernel(&nums[0], n_samples)
    elif method == 'insertion':
        insertionSortKernel(&nums[0], n_samples)
    else:
        raise Exception('Method %s not supported yet'%method)

    return

def sort(nums, method=None):
    """
    :param nums: array of np.ndarray. if nums is a list, will create a new np.ndarray from it.
    :param method: one of [radix, bubble], when method is None, use python's default `sorted` method
    :return:
    """
    if method is None:
        return sorted(nums)
    elif method == 'radix':
        return radix_sort(nums)
    else:
        nums = py_data_to_c_data(nums,copy=False)
        sort_kernel(nums,method=method)
        return nums
