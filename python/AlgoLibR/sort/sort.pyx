# distutils: language = c++
import cython
cimport cython
from cpython cimport array
from csort cimport radix_sort_kernel,bubbleSortKernel

ctypedef fused real:
    cython.short
    cython.ushort
    cython.int
    cython.uint
    cython.long
    cython.ulong
    cython.longlong
    cython.ulonglong
    cython.float
    cython.double



def radix_sort(nums):
    cdef size_t n_samples = len(nums)

    cdef array.array h_in = array.array('I',nums)
    cdef array.array h_out = array.array('I',[0 for _ in range(n_samples)])
    cdef unsigned int[:] h_out_py = h_out


    radix_sort_kernel(h_in.data.as_uints, h_out.data.as_uints, n_samples)

    del h_in
    return h_out.tolist()


def bubble_sort(real[:] nums):
    bubbleSortKernel(&nums[0], nums.shape[0])


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
        bubble_sort(nums)
    else:
        raise Exception('Method %s not supported yet'%method)
