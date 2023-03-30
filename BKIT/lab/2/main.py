from lab_python_oop.rectangle import Rectangle
from lab_python_oop.circle import Circle
from lab_python_oop.square import Square

import requests

N = 20

def main():
    r = Rectangle(N, N, "синего")
    c = Circle(N, "зеленого")
    s = Square(N, "красного")
    print(r)
    print(c)
    print(s)

    print('\n\nВызов метода из сторонней библиотеки:')
    r = requests.get('https://api.github.com/events')
    print(r.encoding)

if __name__ == "__main__":
    main()