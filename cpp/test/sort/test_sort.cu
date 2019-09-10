#include "common/utils.h"
#include "sort/sort.h"
#include <stdio.h>
#define N 10


int main(int argc, char *argv[]){
    unsigned int arrs[N] = {5,14,2,16,21,651,61,21,65,16};
    unsigned int h_outs[N];
    unsigned int *d_in, *d_out;

    cudaMalloc((void **)&d_in, N* sizeof(unsigned int));
    cudaMalloc((void **)&d_out, N* sizeof(unsigned int));
    checkCudaErrors(cudaGetLastError());

    cudaMemcpy(d_in, arrs, N * sizeof(unsigned int), cudaMemcpyHostToDevice);
    checkCudaErrors(cudaGetLastError());

    SORT::radix_sort(d_in, d_out,  (size_t) N);

    cudaMemcpy(h_outs,d_out, N * sizeof(unsigned int), cudaMemcpyDeviceToHost);

    for(int i = 0; i < N; i++){
        printf("%d ",h_outs[i]);
    }
    printf("\n");

    checkCudaErrors(cudaFree(d_in));
    checkCudaErrors(cudaFree(d_out));
}
