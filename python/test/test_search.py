import numpy as np
from AlgoLibR.search import search


def test_seach(test_count=10):
    for search_method in ['binary_search', 'jump_search']:
        sucess_cnt = 0
        for _ in range(test_count):
            nums = np.random.randint(1, 10000, 300)
            nums.sort()
            target_index = np.random.choice(nums.shape[0])
            target = nums[target_index]

            candidate_index = search(nums, target, method=search_method, ascending=True,isExist=True)
            assert candidate_index == target_index

            target_index = np.random.choice(nums.shape[0])
            nums = nums[::-1]
            target = nums[target_index]
            candidate_index = search(nums, target, method=search_method, ascending=False,isExist=True)
            assert candidate_index == target_index