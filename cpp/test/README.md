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

### 中文分词测试效果
使用[结巴中文分词](https://github.com/fxsjy/jieba)的的词典，对一段文本进行测试


>《三国演义》描写了从东汉末年到西晋初年之间近百年的历史风云，以描写战争为主，诉说了东汉末年的群雄割据混战和魏、蜀、吴三国之间的政治和军事斗争，最终司马炎一统三国，建立晋朝的故事。反映了三国时代各类社会斗争与矛盾的转化，并概括了这一时代的历史巨变，塑造了一群叱咤风云的三国英雄人物。

本方法的分词效果  
>《 三国演义 》 描写 了 从 东汉 末年 到 西晋 初年 之间 近百 年 的 历史风云 ， 以 描写 战争 为主 ， 诉说 了 东汉 末年 的 群雄割据 混战 和 魏 、 蜀 、 吴三国 之间 的 政治 和 军事 斗争 ， 最终 司马炎 一统 三国 ， 建立 晋朝 的 故事 。 反映 了 三国 时代 各类 社会 斗争 与 矛盾 的 转化 ， 并 概括 了  这 一时 代 的 历史 巨变 ， 塑造 了 一群 叱咤风云 的 三国 英雄人物 。


jieba的分词效果
> 《 三国演义 》 描写 了 从 东汉 末年 到 西晋 初年 之间 近 百年 的 历史风云 ， 以 描写 战争 为主 ， 诉说 了 东汉 末年 的 群雄割据 混战 和 魏 、 蜀 、 吴三国 之间 的 政治 和 军事 斗争 ， 最终 司马炎 一统 三国 ， 建立 晋朝 的 故事 。 反映 了 三国 时代 各类 社会 斗争 与 矛盾 的 转化 ， 并 概括 了 
这 一 时代 的 历史 巨变 ， 塑造 了 一群 叱咤风云 的 三国 英雄人物 。

