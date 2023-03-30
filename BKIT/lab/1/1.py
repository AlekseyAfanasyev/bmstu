import sys
import math

def getNumbersFromConsole():
    A, B, C = 0, 0, 0
    while True:
        try:
            A, B, C = map(float, input().split(' '))
        except:
            print('Error occured while input. Try again.')
            continue
        break
    return A, B, C

def getNumbersFromArguments():
    result = []
    for i in range(1, 4):
        try:
            result.append(float(sys.argv[i]))
        except:
            return []
    return result

def getEquationRoots(A, B, C):
    D = B*B - 4*A*C
    if A == 0:
        if B == 0:
            return []
        else:
            return [-math.sqrt(math.abs(-C/B)), math.sqrt(math.abs(-C/B))]
    if D < 0:
        return []
    elif D == 0:
        try:    
            X1 = -math.sqrt( (-B)/(2 * A) )
            X2 = math.sqrt( (-B)/(2*A) )
        except:
            return []
        return list(set([X1, X2]))
    else:
        result = []
        firstPair = True
        secondPair = True
        try:
            X1 = -math.sqrt((-B + math.sqrt(D))/(2 * A))
            X2 = math.sqrt((-B + math.sqrt(D))/(2 * A))
        except:
            firstPair = False
        try:
            X3 = -math.sqrt((-B - math.sqrt(D))/(2 * A))
            X4 = math.sqrt((-B - math.sqrt(D))/(2 * A))
        except:
            secondPair = False
        
        if firstPair:
            result.append(X1)
            result.append(X2)
        if secondPair:
            result.append(X3)
            result.append(X4)
        return list(set(result))

def main():
    numbers = getNumbersFromArguments()
    if len(numbers) == 0:
        print('No numbers in arguments found.')
        print('Please input numbers via console:')
        numbers = getNumbersFromConsole()
    roots = getEquationRoots(numbers[0], numbers[1], numbers[2])
    rootsAmount = len(roots)
    if rootsAmount == 0:
        print('No real solutions')
    elif rootsAmount == 1:
        print('The only solution is: ' + str(roots[0]))
    else:
        print('The roots are:')
        for i in range(len(roots)):
            print('X' + str(i+1) + ' = ' + str(roots[i]))


if __name__ == "__main__":
    main()