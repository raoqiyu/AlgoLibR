'''
Author: raoqiyu@gmail.com
Date: 2020-01-13 17:59:08
FilePath: /AlgoLibR/test.py
Description: 
'''

import numpy as np
from AlgoLibR.sort.sort import sort
from AlgoLibR.search.search import search


def test_sort(test_count=10):
    for sort_method in ['bubble', 'quick', 'insertion', 'selection']:
        sucess_cnt, failure_cnt = 0, 0
        for _ in range(test_count):
            nums = np.random.randint(1,100000,300)
            nums_np_sorted = nums.copy()
            nums_np_sorted.sort()

            nums_sorted = sort(nums.copy(), method=sort_method, ascending=False)
            if np.all(nums_np_sorted[::-1] == nums_sorted):
                sucess_cnt += 1
            else:
                failure_cnt += 1
                print(sort_method, 'descending failure')
            nums_sorted = sort(nums.copy(), method=sort_method, ascending=True)
            if np.all(nums_np_sorted == nums_sorted):
                sucess_cnt += 1
            else:
                failure_cnt += 1
                print(sort_method, 'ascending failure') 
        print(sort_method, '_sort sucess count %d/%d'%(sucess_cnt, test_count*2))

def test_seach(test_count=10):
    for search_method in ['binary_search']:
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
        print(search_method, 'sucess count %d/%d'%(sucess_cnt, test_count))


if  __name__ == '__main__':
    test_sort()
    test_seach()



