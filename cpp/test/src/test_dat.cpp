//
// Created by raoqiyu on 2020/9/16.
//


#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "AlgoLibR/data_structure/trie/double_array_trie.hpp"

using namespace AlgoLibR::data_structure::trie::dat;

TEST(test_dat, fetch_siblings){
    auto dat = DoubleArrayTrie<int>();
    std::vector<std::wstring> keys{L"一开始",L"一心", L"一心一意",L"二龙戏珠",L"三阳开泰",L"三三两两"};
    dat.setKeys(keys);

    DATNode  root;
    root.depth = 0;
    root.left = 0;
    root.right = keys.size();


    std::vector<DATNode> siblings;
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 3);

    ASSERT_EQ(siblings[0].chr, 1); // 一, depth 1
    ASSERT_EQ(siblings[0].depth, 1);
    ASSERT_EQ(siblings[0].left, 0);
    ASSERT_EQ(siblings[0].right, 3);
    ASSERT_EQ(dat.getCharById(siblings[0].chr), L'一');

    ASSERT_EQ(siblings[1].chr, 2); // 二 , depth 1
    ASSERT_EQ(siblings[1].depth, 1);
    ASSERT_EQ(siblings[1].left, 3);
    ASSERT_EQ(siblings[1].right, 4);
    ASSERT_EQ(dat.getCharById(siblings[1].chr), L'二');

    ASSERT_EQ(siblings[2].chr, 3); // 三 , depth 1
    ASSERT_EQ(siblings[2].depth, 1);
    ASSERT_EQ(siblings[2].left, 4);
    ASSERT_EQ(siblings[2].right, 6);
    ASSERT_EQ(dat.getCharById(siblings[2].chr), L'三');

    root.depth = 1;
    root.left = 0;
    root.right = 3;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 2);

    ASSERT_EQ(siblings[0].chr, 4); // 开, depth 2
    ASSERT_EQ(siblings[0].depth, 2);
    ASSERT_EQ(siblings[0].left, 0);
    ASSERT_EQ(siblings[0].right, 1);
    ASSERT_EQ(dat.getCharById(siblings[0].chr), L'开');

    ASSERT_EQ(siblings[1].chr, 5); // 心 , depth 2
    ASSERT_EQ(siblings[1].depth, 2);
    ASSERT_EQ(siblings[1].left, 1);
    ASSERT_EQ(siblings[1].right, 3);
    ASSERT_EQ(dat.getCharById(siblings[1].chr), L'心');

    root.depth = 1;
    root.left = 3;
    root.right = 6;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 3);

    ASSERT_EQ(siblings[0].chr, 6); // 龙, depth 2
    ASSERT_EQ(siblings[0].depth, 2);
    ASSERT_EQ(dat.getCharById(siblings[0].chr), L'龙');

    ASSERT_EQ(siblings[1].chr, 7); // 阳 , depth 2
    ASSERT_EQ(siblings[1].depth, 2);
    ASSERT_EQ(dat.getCharById(siblings[1].chr), L'阳');

    ASSERT_EQ(siblings[2].chr, 3); // 三 , depth 2
    ASSERT_EQ(siblings[2].depth, 2);
    ASSERT_EQ(dat.getCharById(siblings[2].chr), L'三');


    root.depth = 2;
    root.left = 0;
    root.right = 1;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 1);

    ASSERT_EQ(siblings[0].chr, 8); // 一开 -> 始, depth 3
    ASSERT_EQ(siblings[0].depth, 3);
    ASSERT_EQ(siblings[0].left, 0);
    ASSERT_EQ(siblings[0].right, 1);
    ASSERT_EQ(dat.getCharById(siblings[0].chr), L'始');

    root.depth = 2;
    root.left = 1;
    root.right = 3;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 2);

    ASSERT_EQ(siblings[0].chr, 0); // 一心 -> 一, depth 3
    ASSERT_EQ(siblings[0].depth, 3);
    ASSERT_EQ(siblings[0].left, 1);
    ASSERT_EQ(siblings[0].right, 2);
    ASSERT_EQ(dat.getCharById(siblings[0].chr), L'\0');

    ASSERT_EQ(siblings[1].chr, 1); // 一心 -> 一, depth 3
    ASSERT_EQ(siblings[1].depth, 3);
    ASSERT_EQ(siblings[1].left, 2);
    ASSERT_EQ(siblings[1].right, 3);
    ASSERT_EQ(dat.getCharById(siblings[1].chr), L'一');

}

TEST(test_dat, insert_siblings_basic) {
    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale("zh_CN.utf-8"));

    auto dat = DoubleArrayTrie<int>();

//    std::vector<std::wstring> keys{L"一开始",L"一心", L"一心一意",L"二龙戏珠",L"三阳开泰",L"三三两两"};
    std::vector<std::wstring> keys{L"一开",L"一心", L"一心一"};//, L"一心一意",L"二龙戏珠",L"三阳开泰",L"三三两两"};
    dat.setKeys(keys);

    DATNode  root;
    root.depth = 0;
    root.left = 0;
    root.right = keys.size();

    std::vector<DATNode> siblings;
    std::unordered_set<int> used;

    // root's neighbor: 一
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 1);
    ASSERT_EQ(siblings[0].chr, 1);

    // 一's neighbor: 开,心
    std::vector<DATNode> sub_siblings;
    dat.fetchSibling(siblings[0], sub_siblings);
    ASSERT_EQ(sub_siblings.size(), 2);
    ASSERT_EQ(dat.getCharById(sub_siblings[0].chr), L'开');
    ASSERT_EQ(dat.getCharById(sub_siblings[1].chr), L'心');

    // 开's neighbor: \0
    siblings.clear();
    dat.fetchSibling(sub_siblings[0], siblings);
    ASSERT_EQ(siblings.size(), 1);
    ASSERT_EQ(siblings[0].left, 0);
    ASSERT_EQ(siblings[0].right, 1);
    ASSERT_EQ(siblings[0].depth, 3);
    ASSERT_EQ(dat.getCharById(siblings[0].chr), L'\0');


    // \0's neighbor: null
    sub_siblings.clear();
    dat.fetchSibling(siblings[0], sub_siblings);
    ASSERT_EQ(sub_siblings.size(), 0);


    // root's neighbor: 一
    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 1);
    ASSERT_EQ(siblings[0].chr, 1);
    size_t parent_pos = 1;
    dat.insertSibling(siblings, parent_pos, used);

    for(auto v:dat.base) std::wcout << v << ' ';
    std::wcout << std::endl;
    for(auto v:dat.check) std::wcout << v << ' ';
    std::wcout << std::endl;
    std::flush(std::wcout);

    ASSERT_NE(-1, dat.exactMatchSearch(keys[0]));
    ASSERT_EQ(1, dat.exactMatchSearch(keys[0]));
    ASSERT_EQ(2, dat.exactMatchSearch(keys[1]));
    ASSERT_EQ(3, dat.exactMatchSearch(keys[2]));
//    std::cout << dat.exactMatchSearch(keys[1]) << std::endl;
}

TEST(test_dat, insert_siblings_basic_2) {
    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale("zh_CN.utf-8"));

    auto dat = DoubleArrayTrie<int>();

    std::vector<std::wstring> keys{L"一开始", L"一心", L"一心一意", L"三三两两", L"三阳开泰", L"二龙戏珠"};
//    std::vector<std::wstring> keys{L"一开",L"一心"};//, L"一心一意",L"二龙戏珠",L"三阳开泰",L"三三两两"};
    dat.setKeys(keys);

    DATNode  root;
    root.depth = 0;
    root.left = 0;
    root.right = keys.size();

    std::vector<DATNode> siblings;
    std::unordered_set<int> used;

    // root's neighbor: 一
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 3);
    ASSERT_EQ(siblings[0].chr, 1);

    // 一's neighbor: 开,心
    std::vector<DATNode> sub_siblings;
    dat.fetchSibling(siblings[0], sub_siblings);
    ASSERT_EQ(sub_siblings.size(), 2);
    ASSERT_EQ(dat.getCharById(sub_siblings[0].chr), L'开');
    ASSERT_EQ(dat.getCharById(sub_siblings[1].chr), L'心');

    // 开's neighbor: 始
    siblings.clear();
    dat.fetchSibling(sub_siblings[0], siblings);
    ASSERT_EQ(siblings.size(), 1);
    ASSERT_EQ(siblings[0].left, 0);
    ASSERT_EQ(siblings[0].right, 1);
    ASSERT_EQ(siblings[0].depth, 3);
    ASSERT_EQ(dat.getCharById(siblings[0].chr), L'始');


    // 始's neighbor: \0
    sub_siblings.clear();
    dat.fetchSibling(siblings[0], sub_siblings);
    ASSERT_EQ(sub_siblings.size(), 1);


    // root's neighbor: 一
    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 3);
    ASSERT_EQ(siblings[0].chr, 1);

    size_t parent_pos = 1;
    dat.insertSibling(siblings, parent_pos, used);
    std::flush(std::wcout);

    for(auto v:dat.base) std::wcout << v << ' ';
    std::wcout << std::endl;
    for(auto v:dat.check) std::wcout << v << ' ';
    std::wcout << std::endl;
    std::flush(std::wcout);
//
    ASSERT_EQ(1, dat.exactMatchSearch(keys[0]));
    ASSERT_EQ(2, dat.exactMatchSearch(keys[1]));
    ASSERT_EQ(3, dat.exactMatchSearch(keys[2]));
    ASSERT_EQ(4, dat.exactMatchSearch(keys[3]));
    ASSERT_EQ(5, dat.exactMatchSearch(keys[4]));
//    ASSERT_EQ(6, dat.exactMatchSearch(keys[5]));
//    std::cout << dat.exactMatchSearch(keys[1]) << std::endl;
}


class test_data_insert_siblings: public::testing::TestWithParam<std::vector<std::wstring>>{

};


TEST_P(test_data_insert_siblings, insert_siblings_utils) {
    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale("zh_CN.utf-8"));

    auto dat = DoubleArrayTrie<int>();

    std::vector<std::wstring> keys = GetParam();
    dat.setKeys(keys);

    DATNode  root;
    root.depth = 0;
    root.left = 0;
    root.right = keys.size();

    std::vector<DATNode> siblings;
    std::unordered_set<int> used;
    size_t parent_pos = 1;


    dat.fetchSibling(root, siblings);
    dat.insertSibling(siblings, parent_pos, used);
    std::flush(std::wcout);

    std::wstring tmp;
    for(auto i = 0 ; i < keys.size(); i++){
        ASSERT_EQ(i+1, dat.exactMatchSearch(keys[i]));
        tmp = keys[i].substr(1, (size_t) keys[i].size()-1);
        ASSERT_EQ(-1, dat.exactMatchSearch(tmp));
    }
}


INSTANTIATE_TEST_CASE_P(test_with_keys,
                        test_data_insert_siblings,
                        testing::Values(std::vector<std::wstring>{L"lie", L"like", L"人民", L"民生", L"浙江"},
                                        std::vector<std::wstring>{L"lie", L"like", L"人民"},
                                        std::vector<std::wstring>{L"一举", L"一举一动", L"一举成名", L"一举成名天下知",
                                                                  L"万能", L"万能胶"}
                                        )
                        );


TEST(test_dat, query_value) {
    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale("zh_CN.utf-8"));

    std::vector<std::wstring> keys{L"一开始", L"一心", L"一心一意", L"三三两两", L"三阳开泰", L"二龙戏珠"};
    std::vector<char> values{'A', 'B', 'C', 'D', 'E', 'F'};;

    auto dat = DoubleArrayTrie<char>();

    dat.build(keys, values);

    std::wstring k1{L"哈哈"}, k2{L"测试"};
    ASSERT_EQ(NULL, dat.get(k1));
    ASSERT_EQ(NULL, dat[k2]);

    ASSERT_EQ('A', dat.get(keys[0]));
    ASSERT_EQ('B', dat.get(keys[1]));
    ASSERT_EQ('C', dat.get(keys[2]));
    ASSERT_EQ('D', dat.get(keys[3]));
    ASSERT_EQ('E', dat.get(keys[4]));
    ASSERT_EQ('F', dat.get(keys[5]));

    ASSERT_EQ('A', dat[keys[0]]);
    ASSERT_EQ('B', dat[keys[1]]);
    ASSERT_EQ('C', dat[keys[2]]);
    ASSERT_EQ('D', dat[keys[3]]);
    ASSERT_EQ('E', dat[keys[4]]);
    ASSERT_EQ('F', dat[keys[5]]);

}
