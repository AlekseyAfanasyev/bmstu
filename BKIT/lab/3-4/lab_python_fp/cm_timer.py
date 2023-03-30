from time import *
from contextlib import *
class cm_timer_1():

    def __init__(self):
        self.start = 0
        self.finish = 0
        
    def __enter__(self):
        self.start = time()
        
    def __exit__(self, ex_type, ex_value, ex_traceback):
        self.finish = time()
        print("time: ", self.finish - self.start)


@contextmanager
def cm_timer_2():
    start = time()
    yield None
    finish = time()
    print("time: ", finish - start)

def main():
    with cm_timer_1():
        sleep(1.5)
    with cm_timer_2():
        sleep(2)

if __name__ == "__main__":
    main()