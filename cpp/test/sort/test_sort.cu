#include "common/utils.h"
#include "sort/sort.h"
#include <stdio.h>
#define N 10


int main(int argc, char *argv[]){
    unsigned int h_in[N] = {5,14,2,16,21,651,61,21,65,16};
    unsigned int h_outs[N];

    SORT::radix_sort(h_in, h_outs,  (size_t) N);

    for(int i = 0; i < N; i++){
        printf("%d ",h_outs[i]);
    }
    printf("\n");
}
