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

def bubble_sort(real[:] nums):
    bubbleSortKernel(&nums[0], nums.shape[0])
    return

def quick_sort(real[:] nums):
    cdef long n_samples = nums.shape[0]
    quickSortKernel(&nums[0], n_samples)
    return

def selection_sort(real[:] nums):
    cdef unsigned int n_samples = nums.shape[0]
    selectionSortKernel(&nums[0], n_samples)
    return

def insertion_sort(real[:] nums):
    cdef unsigned int n_samples = nums.shape[0]
    insertionSortKernel(&nums[0], n_samples)
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
    elif method == 'bubble':
        nums = py_data_to_c_data(nums,copy=False)
        bubble_sort(nums)
        return nums
    elif method == 'quick':
        nums = py_data_to_c_data(nums,copy=False)
        quick_sort(nums)
        return nums
    elif method == 'selection':
        nums = py_data_to_c_data(nums,copy=False)
        selection_sort(nums)
        return nums
    elif method == 'insertion':
        nums = py_data_to_c_data(nums,copy=False)
        insertion_sort(nums)
        return nums
    else:
        raise Exception('Method %s not supported yet'%method)
