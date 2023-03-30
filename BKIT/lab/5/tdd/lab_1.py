import math

def getEquationRoots(A, B, C):
    result = []
    D = B*B - 4*A*C
    if A == 0:
        if B == 0:
            return []
        else:
            result = [-math.sqrt(math.abs(-C/B)), math.sqrt(math.abs(-C/B))]
    if D < 0:
        return []
    elif D == 0:
        try:    
            X1 = -math.sqrt( (-B)/(2 * A) )
            X2 = math.sqrt( (-B)/(2*A) )
        except:
            return []
        result = list(set([X1, X2]))

    else:
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
        result = list(set(result))
    return sorted(result)
