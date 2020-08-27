import numpy as np
import pytest

from AlgoLibR.sort import sort


@pytest.mark.sort
class Test_Sort:
    def setup_class(self):
        self.nums = np.random.randint(1,100000,30)
        self.nums_np_sorted = self.nums.copy()
        self.nums_np_sorted.sort()

    def fn(self, method):
        print('test sort method:', method)
        nums_sorted = sort(self.nums.copy(), method=method, ascending=False)
        assert np.all(nums_sorted == self.nums_np_sorted[::-1]), (nums_sorted[:5], self.nums_np_sorted[:5])

        nums_sorted = sort(self.nums.copy(), method=method, ascending=True)
        assert np.all(nums_sorted == self.nums_np_sorted), (nums_sorted[:5], self.nums_np_sorted[:5])

    def test_sort(self):
        print()
        for sort_method in ['bubble', 'quick', 'insertion', 'selection', 'count', 'radix', 'heap', 'merge', 'tim']:
            self.fn(sort_method)


