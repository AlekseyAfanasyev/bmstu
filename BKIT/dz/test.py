import unittest
from fib import get_fib_number_at_pos

class FibTestCase(unittest.TestCase):
    def test_number_1(self):
        self.assertEqual(1, get_fib_number_at_pos(1))
    def test_number_3(self):
        self.assertEqual(2, get_fib_number_at_pos(3))
    def test_number_7(self):
        self.assertEqual(13, get_fib_number_at_pos(7))
    def test_number_8(self):
        self.assertEqual(21, get_fib_number_at_pos(8))
    def test_number_9(self):
        self.assertEqual(34, get_fib_number_at_pos(9))