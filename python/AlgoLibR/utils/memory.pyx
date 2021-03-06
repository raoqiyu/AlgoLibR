# distutils: language = c++
'''
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/python/AlgoLibR/utils/memory.pyx
Description: 
'''

cimport cython

import numpy as np
import array


def py_data_to_c_data(data, dtype=None, copy=False):
    """

    :param data:
    :return:
    """
    if type(data) != np.ndarray:
        data_py = np.array(data,dtype=dtype, copy=copy, order='C')
    else:
        if copy:
            data_py = np.copy(data, order='C')
        else:
            if not data.flags['C_CONTIGUOUS']:
                data_py = np.ascontiguousarray(data)
            else:
                data_py = data
    return data_py


def malloc_memory_from_data(data, dtype=None, copy=False):
    """

    :param data:
    :return:
    """
    if copy:
        data_py = np.copy(data, order='C', dtype=dtype)
    else:
        data_py = np.zeros_like(data, order='C', dtype=dtype)
    return data_py


def malloc_memory(size, dtype):
    """
    """
    data_py = np.zeros(size,dtype=dtype)
    return data_py




