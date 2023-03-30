def sort_wo_lambda(data):
    return sorted(data, key=abs, reverse=True)

def sort_lambda(data):
    return sorted(data, key = lambda x: abs(x), reverse=True)

def main():
    data = [4, -30, 30, 100, -100, 123, 1, 0, -1, -4]
    print(sort_lambda(data))
    print(sort_wo_lambda(data))

if __name__ == "__main__":
    main()