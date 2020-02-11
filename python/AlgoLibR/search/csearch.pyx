'''
Author: raoqiyu@gmail.com
Date: 2020-01-16 11:34:39
FilePath: /AlgoLibR/python/AlgoLibR/search/csearch.pyx
Description: 
'''
# cython: profile=False
# distutils: language = c++
# cython: language_level = 3


import cython
cimport cython
import numpy as np
from csearch cimport SEARCH_METHOD, searchKernel
from AlgoLibR.utils.memory import py_data_to_c_data,malloc_memory_from_data
from AlgoLibR.utils.data_types cimport real_number


search_methods = {'binary_search':SEARCH_METHOD.BINARY_SEARCH_M,
                  'jump_search':SEARCH_METHOD.JUMP_SEARCH_M,
                 }  


def search_kernel(real_number[:] nums, real_number target, method, ascending, isExist):
    cdef size_t n_samples = nums.shape[0]

    pos = searchKernel(&nums[0], target, n_samples, search_methods[method], ascending, isExist)
    return pos


def search(nums, target, method='binary_search', ascending=True, isExist=True):
    """
    :param nums: array of np.ndarray. if nums is a list, will create a new np.ndarray from it.
    :param method: use binary search as default method
    :return:
    """
    if method not in search_methods:
        raise Exception('Unsupported method')
    else:
        nums = py_data_to_c_data(nums,copy=False)
        pos = search_kernel(nums, target, method, ascending, isExist)
        return pos