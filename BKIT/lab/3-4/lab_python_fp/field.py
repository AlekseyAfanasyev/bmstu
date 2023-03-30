def field(items, *args):
    assert len(args) > 0
    if not(len(items)):
        return
    for arg in args:
        if not(arg in items[0].keys()):
            return
    if len(args) == 1:
        for item in items:
            yield item[args[0]]
    else:
        for item in items:
            record = {}
            for arg in args:
                record[arg] = item[arg]
            yield record



def main():
    goods = [
    {'title': 'Ковер', 'price': 2000, 'color': 'green'},
    {'title': 'Диван для отдыха', 'price': 5300, 'color': 'black'}
    ]

    gen1 = field(goods, 'title') # должен выдавать 'Ковер', 'Диван для отдыха'
    gen2 = field(goods, 'title', 'price') # должен выдавать {'title': 'Ковер', 'price': 2000}, {'title': 'Диван для отдыха', 'price': 5300}

    for i in gen1:
        print(i, end=' ')
    print()

    for i in gen2:
        print(i, end=' ')
    print()

if __name__ == "__main__":
    main()


