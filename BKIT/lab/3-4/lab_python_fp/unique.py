class Unique(object):
    def __init__(self, items, ignore_case = False, **kwargs):
        self.ignore_case = ignore_case
        self.data = items
        self.occured = set()
        self.index = -1
        pass

    def __next__(self):
        while True:
            self.index += 1
            if self.index >= len(self.data):
                raise StopIteration
            if self.check():
                current = self.data[self.index]
                self.occured.add(current)
                return current

    def __iter__(self):
        return self

    def check(self):
        el = self.data[self.index]
        if self.ignore_case:
            if type(el) == str:
                return not((el.lower() in self.occured) or (el.upper() in self.occured))
            else:
                return not(el in self.occured)
        else:
            return not(el in self.occured)


def main():
    for i in Unique(['a', 'A', 'b', 'B', 'a', 'A', 'b', 'B']):
        print(i)

if __name__ == "__main__":
    main()