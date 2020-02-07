# distutils: language = c++
import cython
cimport cython
import numpy as np
from csort cimport SORT_METHOD, radix_sort_kernel,sortKernel,sortIntegerKernel
from AlgoLibR.utils.memory import py_data_to_c_data,malloc_memory_from_data
from AlgoLibR.utils.data_types cimport real_number,integer_number

sort_methods = {'insertion':SORT_METHOD.INSERTION_SORT_M,
                'bubble':SORT_METHOD.BUBBLE_SORT_M,
                'quick':SORT_METHOD.QUICK_SORT_M,
                'selection':SORT_METHOD.SELECTION_SORT_M,
                'count':SORT_METHOD.COUNT_SORT_M,
                'radix':SORT_METHOD.RADIX_SORT_M,
                'heap':SORT_METHOD.HEAP_SORT_M,
                'merge':SORT_METHOD.MERGE_SORT_M,
                'tim':SORT_METHOD.TIM_SORT_M}


def radix_sort(nums):
    nums = py_data_to_c_data(nums,dtype=np.uint32, copy=False)
    out = malloc_memory_from_data(nums,copy=False)

    cdef cython.uint[:] nums_memview = nums
    cdef cython.uint[:] out_memview = out

    radix_sort_kernel(&nums_memview[0], &out_memview[0], len(nums))

    return out

# do not use cpdef : (Invalid use of fused types, type cannot be specialized)
def sort_kernel(real_number[:] nums, method, ascending):
    cdef size_t n_samples = nums.shape[0]

    sortKernel(&nums[0], n_samples, sort_methods[method], ascending)
    return

def sort_integer_kernel(integer_number[:] nums, method, ascending):
    cdef size_t n_samples = nums.shape[0]

    sortIntegerKernel(&nums[0], n_samples, sort_methods[method], ascending)
    return

def sort(nums, method=None, ascending=True):
    """
    :param nums: array of np.ndarray. if nums is a list, will create a new np.ndarray from it.
    :param method: one of [radix, bubble, insertion, quick, selection], when method is None, use python's default `sorted` method
    :return:
    """
    if method is None:
        return sorted(nums)
    elif method not in sort_methods:
        raise Exception('Unsupported method')
    else:
        nums = py_data_to_c_data(nums,copy=False)
        if method in ['radix','count']:
            sort_integer_kernel(nums, method, ascending)
        else:
            sort_kernel(nums, method, ascending)
        return nums