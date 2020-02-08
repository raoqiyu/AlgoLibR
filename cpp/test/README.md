<!--
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-01-09 14:55:06
 * @FilePath: /AlgoLibR/cpp/test/README.md
 * @Description: 
 -->
Test Code



```bash
# test cpp 
g++ -std=c++11 -I/usr/local/cuda/include -I../ -L/usr/local/lib/ -lAlgoLibR -lAlgoLibR++ test.cpp -o test
./test
Test Heap
Current max: 100
Current max: 45
Current max: 6
Current max: 2
Current max: 1


Test sort unsigned int array: radix sort(GPU) and bubble sort
54329 71422 72452 77510 80669
54329 71422 72452 77510 80669

Test sort float array: bubble sort
16516.099609 123.559998 14.200000 1455.099976 14.870000
14.200000 14.870000 123.559998 1455.099976 16516.099609

```
