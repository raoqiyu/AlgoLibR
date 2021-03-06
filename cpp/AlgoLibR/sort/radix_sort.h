/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2019-09-09 14:09:58
 * @FilePath: /AlgoLibR/cpp/AlgoLibR/sort/radix_sort.h
 * @Description: Implementing Parallel Radix Sort with CUDA 
 */

#ifndef RADIX_SORT_H
#define RADIX_SORT_H
#include <cuda_runtime.h>
#include "AlgoLibR/device/gpu/utils.h"

namespace AlgoLibR{
namespace sort{
namespace radix_sort{
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

void radix_sort_kernel(unsigned int*  h_inputVals,
               unsigned int*  h_outputVals,
               const size_t numElems);

} // namespace radix_sort
} // namespace sort
} // namespace AlgoLibR

#endif