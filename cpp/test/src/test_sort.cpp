/*
Author: raoqiyu@gmail.com
Date: 2020-01-09 14:55:06
FilePath: /AlgoLibR/cpp/test/AlgoLibR/test_sort.h
Description: 
 */
#include "AlgoLibR/sort/utils.h"
#include "AlgoLibR/sort/sort.h"
#include <stdio.h>
#include <gtest/gtest.h>

#define N_NUM 5



TEST(test_sort, test_float){
    printf("\nTest sort float array: bubble sort\n");
    float h_in[N_NUM] = {16516.1,123.56,14.2,1455.1,14.87};
    float h_out[N_NUM] = {14.2, 14.87, 123.56, 1455.1, 16516.1};

    for(int i = 0; i < 5; i++){
        printf("%f ",h_in[i]);
    }
    printf("\n");

    AlgoLibR::sort::sortKernel(h_in, (size_t) N_NUM, AlgoLibR::sort::BUBBLE_SORT_M, true);
    ASSERT_EQ(memcmp(h_in, h_out, N_NUM * sizeof(float)), 0);
    for(int i = 0; i < 5; i++){
        printf("%f ",h_in[i]);
    }
    printf("\n");
}