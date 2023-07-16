from math import sqrt


def dataIn():

    with open('../txt-files/A.txt', 'r') as f:
        A = [[int(j) for j in i.split()] for i in f]

    with open('../txt-files/b.txt', 'r') as f:
        b = [int(i) for i in f]

    return A, b


def step(A, b, j):

    # a1 = ||a||
    s = 0
    for i in range(j, len(A)):
        s += A[i][j] * A[i][j]
    a1 = sqrt(s)

    # a - e * ||a||
    temp = [0] * j
    temp.append(A[j][j] - a1)
    for i in range(j + 1, len(A)):
        temp.append(A[i][j])

    # a2 = ||a - e * ||a||||
    s = 0
    for i in range(len(A)):
        s += temp[i] * temp[i]
    a2 = sqrt(s)

    w = [temp[i] / a2 for i in range(len(temp))]

    wwT = [[0.0] * len(A) for _ in range(len(A))]
    for i in range(len(temp)):
        for j in range(len(temp)):
            wwT[i][j] = w[i] * w[j]

    U = [[0.0] * len(A) for _ in range(len(A))]
    for i in range(len(A)):
        for j in range(len(A)):
            U[i][j] = int(i == j) - 2 * wwT[i][j]

    A1 = [[0] * len(A) for _ in range(len(A))]
    for i in range(len(A)):
        for j in range(len(A)):
            for k in range(len(A)):
                A1[i][j] += U[i][k] * A[k][j]

    b1 = []
    for i in range(len(A)):
        s = 0
        for j in range(len(A)):
            s += U[j][i] * b[j]
        b1.append(s)

    return A1, b1


def reflections(A, b):

    for j in range(len(A) - 1):
        A, b = step(A, b, j)

    return A, b


def backSub(A1, b1):

    lenA1 = len(A1)

    x = [0] * lenA1
    x[lenA1 - 1] = round(b1[lenA1 - 1] / A1[lenA1 - 1][lenA1 - 1])

    for i in range(lenA1 - 2, -1, -1):
        s = b1[i]
        for j in range(lenA1 - 1, i, -1):
            s -= A1[i][j] * x[j]
        x[i] = round(s / A1[i][i])

    return x


def dataOut(x):
    with open('../txt-files/x.txt', 'w') as f:
        for i in x:
            f.write(str(i) + '\n')


AIn, bIn = dataIn()
AOut, bOut = reflections(AIn, bIn)
xOut = backSub(AOut, bOut)
dataOut(xOut)
