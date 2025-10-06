import unittest
from sorting_algorithms import bubble_sort

class TestBubbleSort(unittest.TestCase):
    def test_sorted_list(self):
        self.assertEqual(bubble_sort([3, 1, 2]), [1, 2, 3])
    
    def test_already_sorted(self):
        self.assertEqual(bubble_sort([1, 2, 3]), [1, 2, 3])
    
    def test_reverse_list(self):
        self.assertEqual(bubble_sort([5, 4, 3, 2, 1]), [1, 2, 3, 4, 5])
    
    def test_empty_list(self):
        self.assertEqual(bubble_sort([]), [])

if __name__ == '__main__':
    unittest.main()
