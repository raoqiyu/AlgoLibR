<!--
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-09 14:55:06
 * @FilePath: /AlgoLibR/cpp/test/README.md
 * @Description: 
 -->
Test CUDA Code




```bash
# test gpu radix sort
nvcc --include-path=../../../cpp/src  -c sort.o sort.cu

nvcc ../../src/sort/sort.o test_sort.cu -o test_sort --include-path=../../../cpp/src

./test_sort

2 5 14 16 16 21 21 61 65 651
```
---

```bash
# test cpp 
g++ -I../src -L/usr/local/lib/ -lAlgoLibR test.cpp -o test

./test
Test Heap
Current max: 100
Current max: 45
Current max: 6
Current max: 2
Current max: 1


```
