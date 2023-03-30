import json

from lab_python_fp.print_result import print_result
from lab_python_fp.gen_random import gen_random
from lab_python_fp.cm_timer import cm_timer_1
from lab_python_fp.unique import Unique
from lab_python_fp.field import field

path = 'data_light.json'

with open(path, encoding='utf-8') as f:
    data = json.load(f)

@print_result
def f1(arg):
    return sorted(list(j for j in Unique(list(i for i in field(arg, 'job-name')))), key=lambda x: x.lower())


@print_result
def f2(arg):
    return list(filter(lambda s: (s.split())[0].lower() == 'программист', arg))


@print_result
def f3(arg):
    return list(map(lambda lst: lst + ' с опытом Python', arg))


@print_result
def f4(arg):
    return dict(zip(arg, ['зарплата ' + str(i) + ' руб.' for i in gen_random(len(arg), 100000, 200000)]))


def main():
    with cm_timer_1():
        f4(f3(f2(f1(data))))
 
main()