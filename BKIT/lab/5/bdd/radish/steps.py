# -*- coding: utf-8 -*-

from radish import given, when, then
from sys import path

path.append('.')
from lab_1.equation_solver import getEquationRoots

@given("I have the numbers {A:g}, {B:g} and {C:g}")
def have_numbers(step, A, B, C):
    step.context.A = A
    step.context.B = B
    step.context.C = C

@when("I solve the equation with those numbers")
def sum_numbers(step):
    step.context.N = len(getEquationRoots( \
       step.context.A, step.context.B, step.context.C))

@then("I expect to get {N:g} roots")
def expect_result(step, N):
    assert step.context.N == N