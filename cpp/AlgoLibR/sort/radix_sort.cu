/*
@File    :   sort.cu
@Time    :   2019/09/09 15:10:32
@Author  :   raoqiyu@gmail.com
@Desc    :   Implementing Parallel Radix Sort with CUDA
*/

#include "AlgoLibR/sort/radix_sort.h"
#include <stdio.h>
#include <cuda_runtime.h>


namespace AlgoLibR{
namespace sort{
namespace radix_sort{

__global__
void histogram(const unsigned int * const d_in, unsigned int * const d_out, const int nthBit, const size_t numElems){
    //use shared memory to load the whole block data
    extern __shared__ unsigned int tempElems[];

    unsigned int idx = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int tid = threadIdx.x;

    if(idx < numElems){
        tempElems[tid] = d_in[idx];
        __syncthreads();
        unsigned int nthBin = (tempElems[tid]>>nthBit)&(numBins-1);
        atomicAdd(&d_out[nthBin],1);
    }
}

// Hillis Steele Scan
__global__
void scan(const unsigned int * const d_in, unsigned int *d_out, unsigned int *d_blockLastElems, const size_t numElems){
    // use shared memory to load the whole block data
    extern __shared__ unsigned int temp[];

    unsigned int tid = threadIdx.x;
    unsigned int idx = blockIdx.x*blockDim.x + tid;

    if(idx >= numElems){
        return;
    }

    temp[tid] = d_in[idx];
    __syncthreads();

    for(unsigned int stride = 1; stride < blockDim.x; stride <<= 1){
        unsigned int tmpVal = temp[tid];
        __syncthreads();

        if(tid + stride < blockDim.x)
            temp[tid+stride] += tmpVal;
        __syncthreads();
    }

    // exclusive scan
    d_out[idx] = tid > 0 ? temp[tid-1] : 0;

    if(tid  == (blockDim.x-1))
        d_blockLastElems[blockIdx.x] = temp[tid];
}

__global__
void add(const unsigned int * const d_in, unsigned int * const d_out, const size_t numElems){
    unsigned int bIdx = blockIdx.x;
    unsigned int idx = bIdx*blockDim.x + threadIdx.x;

    // The last element of the previous block should be added to current block's element
    if (idx < numElems){
        d_out[idx]  += d_in[bIdx];
    }

}


// Exclusive Prefix Sum of Histogram(support a large array, not just in one block)
// 1) first do scan on each block
// 2) then do scan one all block's last elements
// 3) then add block's last element to its next block
void prefixSum(unsigned int *d_in, unsigned int *d_out, const size_t numElems){
    const dim3 blockSize(min(1024, (int)numElems));
    const dim3 gridSize(ceil((float)numElems/blockSize.x));


    unsigned int *d_blockLastElems;
    checkCudaErrors(cudaMalloc((void**)&d_blockLastElems, gridSize.x*sizeof(unsigned int)));

    // 1) first do scan on each block
    scan<<<gridSize, blockSize, blockSize.x*sizeof(unsigned int)>>>(d_in, d_out, d_blockLastElems, numElems);
    cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

    if(gridSize.x > 1){
        // 2) then do scan one all block's last elements
        prefixSum(d_blockLastElems, d_blockLastElems, gridSize.x);
        cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

        // 3) then add block's last element to its next block
        add<<<gridSize, blockSize>>>(d_blockLastElems, d_out, numElems);
        cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
    }
    checkCudaErrors(cudaFree(d_blockLastElems));
}

__global__
void map(const unsigned int * const d_in, unsigned int * const d_out, const size_t numElems, const int mask, const int nthBit){
    unsigned int idx = blockIdx.x*blockDim.x + threadIdx.x;
    if(idx < numElems){
        d_out[idx] = ((d_in[idx]>>nthBit)&(numBins-1)) == mask;
    }
}
__global__
void movebyBins(unsigned int* const d_inputVals,unsigned int* const d_outputVals,
          unsigned int* const d_binElems, unsigned int *d_binScan , unsigned int *d_binHistogram, const size_t numElems, const int mask){
    unsigned int idx = blockIdx.x*blockDim.x + threadIdx.x;

    if(idx < numElems && d_binElems[idx] == 1){
        unsigned int outputIdx = d_binHistogram[mask] + d_binScan[idx];
        d_outputVals[outputIdx] = d_inputVals[idx];
    }
}

void radix_sort_kernel(unsigned int*  h_inputVals,
               unsigned int*  h_outputVals,
               const size_t numElems){

    const dim3 blockSize(1024);
    const dim3 gridSize(ceil((float)numElems/1024));

    unsigned int *d_binHistogram, *d_binScan, *d_binElems, *d_inputVals,*d_outputVals;
    checkCudaErrors(cudaMalloc((void **)&d_inputVals, numElems* sizeof(unsigned int)));
    checkCudaErrors(cudaMalloc((void **)&d_outputVals, numElems* sizeof(unsigned int)));

    checkCudaErrors(cudaMalloc((void**)&d_binHistogram, numBins*sizeof(unsigned int)));
    checkCudaErrors(cudaMalloc((void**)&d_binScan, numElems*sizeof(unsigned int)));
    checkCudaErrors(cudaMalloc((void**)&d_binElems, numElems*sizeof(unsigned int)));

    checkCudaErrors(cudaMemset(d_inputVals,0, numElems*sizeof(unsigned int)));
    checkCudaErrors(cudaMemset(d_outputVals,0, numElems*sizeof(unsigned int)));
    checkCudaErrors(cudaMemset(d_binHistogram,0, numBins*sizeof(unsigned int)));
    checkCudaErrors(cudaMemset(d_binScan,0, numElems*sizeof(unsigned int)));
    checkCudaErrors(cudaMemset(d_binElems,0, numElems*sizeof(unsigned int)));

    checkCudaErrors(cudaMemcpy(d_inputVals, h_inputVals, numElems * sizeof(unsigned int), cudaMemcpyHostToDevice));

    for(int i = 0; i < 8 * (int)sizeof(unsigned int); i += numBits){
        checkCudaErrors(cudaMemset(d_binHistogram,0, numBins*sizeof(unsigned int)));

        // 1) Histogram of the number of occurrences of the i-th bit
        histogram<<<gridSize, blockSize, blockSize.x*sizeof(unsigned int)>>>(d_inputVals, d_binHistogram, i, numElems);
        cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

        // 2) Exclusive Prefix Sum of Histogram
        prefixSum(d_binHistogram, d_binHistogram, numBins);
        cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

        // 3) Determine relative offset of each digit
        // 4) Combine the results of steps 2 & 3 to determine the final output location for each element and move it there
        for(int j = 0; j < numBins; j++){
            map<<<gridSize, blockSize>>>(d_inputVals, d_binElems, numElems, j, i);
            cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

            prefixSum(d_binElems, d_binScan, numElems);
            movebyBins<<<gridSize,blockSize>>>(d_inputVals, d_outputVals, d_binElems,d_binScan,
                                                d_binHistogram, numElems, j);
            cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
        }
        std::swap(d_inputVals, d_outputVals);

    }
    checkCudaErrors(cudaMemcpy(h_outputVals, d_inputVals, numElems*sizeof(unsigned int), cudaMemcpyDeviceToHost));

    checkCudaErrors(cudaFree(d_binHistogram));
    checkCudaErrors(cudaFree(d_binScan));
    checkCudaErrors(cudaFree(d_binElems));
    checkCudaErrors(cudaFree(d_inputVals));
    checkCudaErrors(cudaFree(d_outputVals));
}

} // namespace radix_sort
} // namespace sort
} // namespace AlgoLibR