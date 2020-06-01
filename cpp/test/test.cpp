/*
 * @Author: raoqiyu@gmail.com
 * @Date: 2020-02-01 20:15:16
 * @FilePath: /AlgoLibR/cpp/test/test.cpp
 * @Description: 
 */

#include <locale.h>
#include "src/test_sort.h"
#include "src/test_data_structure.h"
#include "src/test_segment.h"
#include "src/test_regex.h"


int main(){
    std::ios::sync_with_stdio(false);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale(""));
    std::wcout.imbue(std::locale(""));


    // test_ds();
    // test_sort();
    test_segment();
    test_regex_split();
}