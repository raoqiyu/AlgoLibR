//
// Created by raoqiyu on 2020/9/16.
//


#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "AlgoLibR/data_structure/trie/double_array_trie.h"

using namespace AlgoLibR::data_structure::trie::dat;

TEST(test_dat, fetch_siblings){
    auto dat = DoubleArrayTrie();
    std::vector<std::wstring> keys{L"一开始",L"一心", L"一心一意",L"二龙戏珠",L"三阳开泰",L"三三两两"};
    dat.setKeys(keys);

    auto  *root = new DATNode();
    root->depth = 0;
    root->left = 0;
    root->right = keys.size();


    std::vector<DATNode*> siblings;
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 3);

    ASSERT_EQ(siblings[0]->chr, 1); // 一, depth 1
    ASSERT_EQ(siblings[0]->depth, 1);
    ASSERT_EQ(siblings[0]->left, 0);
    ASSERT_EQ(siblings[0]->right, 3);
    ASSERT_EQ(dat.getCharById(siblings[0]->chr), L'一');

    ASSERT_EQ(siblings[1]->chr, 2); // 二 , depth 1
    ASSERT_EQ(siblings[1]->depth, 1);
    ASSERT_EQ(siblings[1]->left, 3);
    ASSERT_EQ(siblings[1]->right, 4);
    ASSERT_EQ(dat.getCharById(siblings[1]->chr), L'二');

    ASSERT_EQ(siblings[2]->chr, 3); // 三 , depth 1
    ASSERT_EQ(siblings[2]->depth, 1);
    ASSERT_EQ(siblings[2]->left, 4);
    ASSERT_EQ(siblings[2]->right, 6);
    ASSERT_EQ(dat.getCharById(siblings[2]->chr), L'三');

    root->depth = 1;
    root->left = 0;
    root->right = 3;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 2);

    ASSERT_EQ(siblings[0]->chr, 4); // 开, depth 2
    ASSERT_EQ(siblings[0]->depth, 2);
    ASSERT_EQ(siblings[0]->left, 0);
    ASSERT_EQ(siblings[0]->right, 1);
    ASSERT_EQ(dat.getCharById(siblings[0]->chr), L'开');

    ASSERT_EQ(siblings[1]->chr, 5); // 心 , depth 2
    ASSERT_EQ(siblings[1]->depth, 2);
    ASSERT_EQ(siblings[1]->left, 1);
    ASSERT_EQ(siblings[1]->right, 3);
    ASSERT_EQ(dat.getCharById(siblings[1]->chr), L'心');

    root->depth = 1;
    root->left = 3;
    root->right = 6;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 3);

    ASSERT_EQ(siblings[0]->chr, 6); // 龙, depth 2
    ASSERT_EQ(siblings[0]->depth, 2);
    ASSERT_EQ(dat.getCharById(siblings[0]->chr), L'龙');

    ASSERT_EQ(siblings[1]->chr, 7); // 阳 , depth 2
    ASSERT_EQ(siblings[1]->depth, 2);
    ASSERT_EQ(dat.getCharById(siblings[1]->chr), L'阳');

    ASSERT_EQ(siblings[2]->chr, 3); // 三 , depth 2
    ASSERT_EQ(siblings[2]->depth, 2);
    ASSERT_EQ(dat.getCharById(siblings[2]->chr), L'三');


    root->depth = 2;
    root->left = 0;
    root->right = 1;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 1);

    ASSERT_EQ(siblings[0]->chr, 8); // 一开 -> 始, depth 3
    ASSERT_EQ(siblings[0]->depth, 3);
    ASSERT_EQ(siblings[0]->left, 0);
    ASSERT_EQ(siblings[0]->right, 1);
    ASSERT_EQ(dat.getCharById(siblings[0]->chr), L'始');

    root->depth = 2;
    root->left = 1;
    root->right = 3;

    siblings.clear();
    dat.fetchSibling(root, siblings);
    ASSERT_EQ(siblings.size(), 2);

    ASSERT_EQ(siblings[0]->chr, 0); // 一心 -> 一, depth 3
    ASSERT_EQ(siblings[0]->depth, 3);
    ASSERT_EQ(siblings[0]->left, 1);
    ASSERT_EQ(siblings[0]->right, 2);
    ASSERT_EQ(dat.getCharById(siblings[0]->chr), L'\0');

    ASSERT_EQ(siblings[1]->chr, 1); // 一心 -> 一, depth 3
    ASSERT_EQ(siblings[1]->depth, 3);
    ASSERT_EQ(siblings[1]->left, 2);
    ASSERT_EQ(siblings[1]->right, 3);
    ASSERT_EQ(dat.getCharById(siblings[1]->chr), L'一');

}