def print_result(fun):
    def decorator(lst = [], *args, **kwargs):
        print(fun.__name__)

        if len(lst):
            result = fun(lst, *args, **kwargs)
        else:
            result = fun(*args, **kwargs)

        if type(result) == dict:
            for key, el in result.items():
                print(f'{key} = {el}')

        elif type(result) == list:
            for i in result:
                print(i)
        else:
            print(result)

        return result

    return decorator


@print_result
def test_1():
    return 1


@print_result
def test_2():
    return 'iu5'


@print_result
def test_3():
    return {'a': 1, 'b': 2}


@print_result
def test_4():
    return [1, 2]


def main():
    print('!!!!!!!!')
    test_1()
    test_2()
    test_3()
    test_4()

if __name__ == "__main__":
    main()