import unittest
from tasks import task_1, task_2, task_3

task_1_result = [('Hammer_3000', '12Hammers Company'), ('Sew_3000', '12Seasons Drills')]
task_2_result = [ ('Super components', 100.0), ('12Hammers Company', 1000.0), ('12Seasons Drills', 1750.0), ('Components company', 5000.0)]
task_3_result = [('12Hammers Company', ['Drill 2', 'Drill 1', 'Multitool']), ('12Seasons Drills', ['Nails', 'Drill 1', 'Multitool'])]

class TasksTestCase(unittest.TestCase):
    def test_task_1(self):
        self.assertEqual(task_1_result, task_1())
    def test_task_2(self):
        self.assertEqual(task_2_result, task_2())
    def test_task_3(self):
        self.assertEqual(task_3_result, task_3())