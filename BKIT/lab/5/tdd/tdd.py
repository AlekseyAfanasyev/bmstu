from lab_1 import getEquationRoots

def tests_get_roots_zero():
    temp = getEquationRoots(1, 2, 3)     
    assert len(temp) == 0
    temp = getEquationRoots(2, 3, 4)     
    assert len(temp) == 0

def tests_get_roots_one():
    temp = getEquationRoots(5, 0, 0) 
    assert temp == [0]

def tests_get_roots_two():
    temp = getEquationRoots(1, 4, -5) 
    assert temp == [-1, 1]

def tests_get_roots_three():
    temp = getEquationRoots(1, -25, 0)   
    assert temp == [-5, 0, 5]
    temp = getEquationRoots(1, -9, 0)   
    assert temp == [-3, 0, 3]

def tests_get_roots_four():
    temp = getEquationRoots(1, -10, 9)     
    assert temp == [-3, -1, 1, 3]   