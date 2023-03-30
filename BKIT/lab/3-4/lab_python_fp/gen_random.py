import random
def gen_random(num_count, begin, end):
    assert begin < end
    assert num_count >= 0

    for i in range(num_count):
        yield random.randint(begin, end)

gen1 = gen_random(1, 2, 3)
gen2 = gen_random(3, 5, 25)

def main():
    for i in gen1:
        print(i, end=' ')
    print()

    for i in gen2:
        print(i, end=' ')

if __name__ == "__main__":
    main()
