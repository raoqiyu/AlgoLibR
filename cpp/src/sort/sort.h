/*
@File    :   sort.h
@Time    :   2019/09/09 14:09:58
@Author  :   raoqiyu@gmail.com
@Desc    :   Implementing Parallel Radix Sort with CUDA
*/
#ifndef SORT_H
#define SORT_H
#include <cuda_runtime.h>
#include "common/utils.h"


namespace SORT{
#define numBits 2
#define numBins (1 << numBits)

__global__
void histogram(const unsigned int * const d_in, const unsigned int * const d_out, const int nthBit, const size_t numElems);

// Hillis Steele Scan
__global__
void scan(const unsigned int * const d_in, unsigned int *d_out, unsigned int *d_blockLastElems, const size_t numElems);

__global__
void add(const unsigned int * const d_in, unsigned int * const d_out, const size_t numElems);

void prefixSum(unsigned int *d_in, unsigned int *d_out, const size_t numElems);

__global__
void map(const unsigned int * const d_in, unsigned int * const d_out, const size_t numElems, const int mask, const int nthBit);

__global__
void movebyBins(unsigned int* const d_inputVals,
          unsigned int* const d_outputVals,
          unsigned int* const d_binElems, unsigned int *d_binScan , unsigned int *d_binHistogram, const size_t numElems, const int mask);

void radix_sort(unsigned int*  h_inputVals,
               unsigned int*  h_outputVals,
               const size_t numElems);
}
#endif