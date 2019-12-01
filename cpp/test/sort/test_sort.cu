//#include "common/utils.h"
#include "sort/radix_sort.h"
#include "sort/bubble_sort.h"
#include <stdio.h>
#define N 5

void test_uints(){
    printf("\nTest unsigned int array\n");
    unsigned int h_in[5] = {71422,72452,54329,77510,80669};
    unsigned int h_outs[N];

    SORT::RADIX_SORT::radix_sort_kernel(h_in, h_outs,  (size_t) N);

    for(int i = 0; i < N; i++){
        printf("%d ",h_outs[i]);
    }
    printf("\n");

    SORT::BUBBLE_SORT::bubbleSortKernel<unsigned int>(h_in, (size_t) N);

    for(int i = 0; i < 5; i++){
        printf("%d ",h_in[i]);
    }
    printf("\n");
}


void test_float(){
    printf("\nTest float array\n");
    float h_in[5] = {16516.1,123.56,14.2,1455.1,14.87};

    for(int i = 0; i < 5; i++){
        printf("%f ",h_in[i]);
    }
    printf("\n");

    SORT::BUBBLE_SORT::bubbleSortKernel(h_in, (size_t) N);

    for(int i = 0; i < 5; i++){
        printf("%f ",h_in[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    test_uints();
    test_float();

}
