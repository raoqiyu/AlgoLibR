//
// Created by raoqiyu on 2020/9/16.
//


#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "AlgoLibR/data_structure/trie/ac_double_array_trie.hpp"

using namespace AlgoLibR::data_structure::trie::ac_dat;

TEST(test_ac_dat, basic_trie_query_value) {

    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale("zh_CN.utf-8"));

    std::vector<std::wstring> keys{L"一开始", L"一心", L"一心一意", L"三三两两", L"三阳开泰", L"二龙戏珠"};
    std::vector<char> values{'A', 'B', 'C', 'D', 'E', 'F'};;

    auto ac_dat = AhoCorasickDoubleArrayTrie<char>();

    ac_dat.build(keys, values);

    std::wstring k1{L"哈哈"}, k2{L"测试"};
    ASSERT_EQ(NULL, ac_dat.get(k1));
    ASSERT_EQ(NULL, ac_dat[k2]);

    ASSERT_EQ('A', ac_dat.get(keys[0]));
    ASSERT_EQ('B', ac_dat.get(keys[1]));
    ASSERT_EQ('C', ac_dat.get(keys[2]));
    ASSERT_EQ('D', ac_dat.get(keys[3]));
    ASSERT_EQ('E', ac_dat.get(keys[4]));
    ASSERT_EQ('F', ac_dat.get(keys[5]));

    ASSERT_EQ('A', ac_dat[keys[0]]);
    ASSERT_EQ('B', ac_dat[keys[1]]);
    ASSERT_EQ('C', ac_dat[keys[2]]);
    ASSERT_EQ('D', ac_dat[keys[3]]);
    ASSERT_EQ('E', ac_dat[keys[4]]);
    ASSERT_EQ('F', ac_dat[keys[5]]);
}

class test_ac_dat_exactMatchSearch: public::testing::TestWithParam<std::vector<std::wstring>>{

};


TEST_P(test_ac_dat_exactMatchSearch, utils) {
    std::vector<std::wstring> keys = GetParam();
    std::vector<char> vals;

    auto ac_dat = AhoCorasickDoubleArrayTrie<char>();
    ac_dat.build(keys, vals);


    std::wstring tmp;
    for(auto i = 0 ; i < keys.size(); i++){
        ASSERT_EQ(i+1, ac_dat.exactMatchSearch(keys[i]));
        tmp = keys[i].substr(1, (size_t) keys[i].size()-1);
        ASSERT_EQ(-1, ac_dat.exactMatchSearch(tmp));
    }
}


INSTANTIATE_TEST_CASE_P(test_with_keys,
                        test_ac_dat_exactMatchSearch,
                        testing::Values(std::vector<std::wstring>{L"lie", L"like", L"人民", L"民生", L"浙江"},
                                        std::vector<std::wstring>{L"lie", L"like", L"人民"},
                                        std::vector<std::wstring>{L"一举", L"一举一动", L"一举成名", L"一举成名天下知",
                                                                  L"万能", L"万能胶"}
                        )
);