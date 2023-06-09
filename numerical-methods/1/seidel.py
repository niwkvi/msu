import numpy as np


def seidel(A, b, eps):

    n = len(A)
    x = np.zeros(n)

    converges = False
    while not converges:
        x_new = np.copy(x)
        for i in range(n):
            s1 = sum(A[i][j] * x_new[j] for j in range(i))
            s2 = sum(A[i][j] * x[j] for j in range(i + 1, n))
            x_new[i] = (b[i] - s1 - s2) / A[i][i]

        converges = np.sqrt(sum((x_new[i] - x[i]) ** 2 for i in range(n))) <= eps
        x = x_new

    return x


AIn = np.loadtxt('A.txt')
bIn = np.loadtxt('b.txt')

xOut = seidel(AIn, bIn, 0.000000000000001)

np.savetxt('x.txt', xOut, fmt='%i')
