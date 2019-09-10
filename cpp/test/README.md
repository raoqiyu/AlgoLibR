Test CUDA Code




```bash
# test radix sort
nvcc --include-path=../../../cpp/src  -c sort.o sort.cu

nvcc ../../src/sort/sort.o test_sort.cu -o test_sort --include-path=../../../cpp/src

./test_sort

2 5 14 16 16 21 21 61 65 651

```
