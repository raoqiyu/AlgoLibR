'''
Author: raoqiyu@gmail.com
Date: 2020-01-13 17:59:08
FilePath: /AlgoLibR/python/test/test.py
Description: 
'''

import numpy as np
from AlgoLibR.sort import sort
from AlgoLibR.search import search


def test_sort(test_count=10):
    for sort_method in ['bubble', 'quick', 'insertion', 'selection', 'count', 'radix', 'heap', 'merge', 'tim']:
        sucess_cnt, failure_cnt = 0, 0
        for _ in range(test_count):
            nums = np.random.randint(1,100000,30)
            nums_np_sorted = nums.copy()
            nums_np_sorted.sort()
            nums_sorted = sort(nums.copy(), method=sort_method, ascending=False)
            if np.all(nums_np_sorted[::-1] == nums_sorted):
                sucess_cnt += 1
            else:
                failure_cnt += 1
                print(sort_method, 'descending failure')
                print(nums)
                print(nums_np_sorted[::-1])
                print(nums_sorted)
            nums_sorted = sort(nums.copy(), method=sort_method, ascending=True)
            if np.all(nums_np_sorted == nums_sorted):
                sucess_cnt += 1
            else:
                failure_cnt += 1
                print(sort_method, 'ascending failure') 
        print(sort_method, 'sort success count %d/%d'%(sucess_cnt, test_count*2))

def test_seach(test_count=10):
    for search_method in ['binary_search', 'jump_search']:
        sucess_cnt = 0
        for _ in range(test_count):
            nums = np.random.randint(1, 10000, 300)
            nums.sort()
            target_index = np.random.choice(nums.shape[0])
            target = nums[target_index]

            candidate_index = search(nums, target, method=search_method, ascending=True,isExist=True)
            if candidate_index == target_index:
                sucess_cnt += 1
            else:
                print(target_index)
                print(candidate_index)
                print(nums[target_index-2:target_index+2])

            target_index = np.random.choice(nums.shape[0])
            nums = nums[::-1]
            target = nums[target_index]
            candidate_index = search(nums, target, method=search_method, ascending=False,isExist=True)
            if candidate_index == target_index:
                sucess_cnt += 1
            else:
                print(target_index)
                print(candidate_index)
                print(nums[target_index-2:target_index+2])

        print(search_method, 'success count %d/%d'%(sucess_cnt, test_count*2))

def test_demo():
    print('\nTest demo')
    from AlgoLibR.demo import PyMyDemo
    a = PyMyDemo(20000)
    print(a.mul(20000))
    a.sayHello('你好')

def test_device():
    print('\nTest device')
    from AlgoLibR.device.gpu import enum_gpu_info
    enum_gpu_info()

def test_segment():
    print('\nTest AC seg')
    from AlgoLibR.ai.nlp.seg import AhoCorasickSegmentor
    ac = AhoCorasickSegmentor()
    ac.Build(b'/home/rqy/AlgoLibR/data/NLP/Dictionary/jieba_dict.txt.big', ' ')

    ret = ac.segment('HEH《三国演义》描写了从东汉末年到西晋初年之间近百年的历史风云，以描写战争为主，诉说了东汉末年的群雄割据混战和魏、蜀、吴三国之间的政治和军事斗争，最终司马炎一统三国，建立晋朝的故事。反映了三国时代各类社会斗争与矛盾的转化，并概括了这一时代的历史巨变，塑造了一群叱咤风云的三国英雄人')
    print(ret)

if  __name__ == '__main__':
    # test_sort()
    # test_seach()
    test_demo() 
    test_segment()
    #test_device()



