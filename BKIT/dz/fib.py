def fib():
    prev, cur = 0, 1
    while True:
        yield cur
        prev, cur = cur, prev+cur
def get_fib_number_at_pos(pos):
    fib_gen = fib()
    number = 0
    for i in range(pos):
        number = next(fib_gen)
    return number