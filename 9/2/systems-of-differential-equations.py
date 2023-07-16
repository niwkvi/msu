from math import *
import numpy as np
import matplotlib.pyplot as plt

m = 1

systems = [
    (lambda x1, x2, t: x2,
     lambda x1, x2, t: -x1),

    (lambda x1, x2, t: sin(m * t) + m * x2,
     lambda x1, x2, t: cos(m * t) - m * x1),

    (lambda x1, x2, t: (2 * x1) / ((x1 ** 2 + x2 ** 2) ** (1/4)) + 10 * x2,
     lambda x1, x2, t: (2 * x2) / ((x1 ** 2 + x2 ** 2) ** (1/4)) - 10 * x1)
]

answers = [
    (lambda t: np.cos(t),
     lambda t: -np.sin(t)),

    (lambda t: t * np.sin(m * t),
     lambda t: t * np.cos(m * t)),

    (lambda t: (t + 1) ** 2 * np.sin(10 * t),
     lambda t: (t + 1) ** 2 * np.cos(10 * t))
]

inits = [
    (1, 0),
    (sin(m), cos(m)),
    (0, 1)
]

intervals = [
    (0, 10),
    (1, 11),
    (0, 10)
]

ns = [10, 50, 100]


def runge1(i, n):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y = np.empty_like(T), np.empty_like(T)
    X[0], Y[0] = inits[i][0], inits[i][1]

    for j in range(1, len(T)):
        X[j] = X[j - 1] + systems[i][0](X[j - 1], Y[j - 1], T[j - 1]) * h
        Y[j] = Y[j - 1] + systems[i][1](X[j - 1], Y[j - 1], T[j - 1]) * h

    return T, X, Y


def runge2(i, n, c):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y = np.empty_like(T), np.empty_like(T)
    X[0], Y[0] = inits[i][0], inits[i][1]

    for j in range(1, len(T)):
        k11 = h * systems[i][0](X[j - 1], Y[j - 1], T[j - 1])
        k12 = h * systems[i][1](X[j - 1], Y[j - 1], T[j - 1])

        k21 = h * systems[i][0](X[j - 1] + k11 / (2 * c), Y[j - 1] + k12 / (2 * c), T[j - 1] + h / (2 * c))
        k22 = h * systems[i][1](X[j - 1] + k11 / (2 * c), Y[j - 1] + k12 / (2 * c), T[j - 1] + h / (2 * c))

        X[j] = X[j - 1] + (1 - c) * k11 + c * k21
        Y[j] = Y[j - 1] + (1 - c) * k12 + c * k22

    return T, X, Y


def runge3(i, n, a2, a3):
    b21, b32 = a2, (a3 * (a2 - a3)) / (a2 * (3 * a2 - 2))
    b31 = a3 - b32
    c2, c3 = (3 * a3 - 2) / (6 * a2 * (a3 - a2)), (3 * a2 - 2) / (6 * a3 * (a2 - a3))
    c1 = 1 - c2 - c3

    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y = np.empty_like(T), np.empty_like(T)
    X[0], Y[0] = inits[i][0], inits[i][1]

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + b21 * k11, Y[j - 1] + b21 * k12, T[j - 1] + a2 * h) * h
        k22 = systems[i][1](X[j - 1] + b21 * k11, Y[j - 1] + b21 * k12, T[j - 1] + a2 * h) * h

        k31 = systems[i][0](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            T[j - 1] + a3 * h) * h
        k32 = systems[i][1](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            T[j - 1] + a3 * h) * h

        X[j] = X[j - 1] + c1 * k11 + c2 * k21 + c3 * k31
        Y[j] = Y[j - 1] + c1 * k12 + c2 * k22 + c3 * k32

    return T, X, Y


def drawGraphs(i, n, p1, p2):
    C, A, B = runge3(i, n, p1, p2)
    realA, realB = answers[i][0](C), answers[i][1](C)
    plt.subplots()
    plt.plot(A, B, color='red')
    plt.plot(realA, realB, color='green')
    plt.show()


def epsilon(X, Y, i):
    s = 0
    for j in range(len(X)):
        s += ((X[j] - answers[i][0](T[j])) ** 2 + Y[j] - answers[i][1](T[j])) / (len(X) ** 2)
    return sqrt(s)


fNum = 2
num = 150
optimal = [100, 0, 0]

for i in np.arange(0, 5, 0.1):
    for j in np.arange(0, 5, 0.1):
        if i != j:
            T, A, B = runge3(fNum, num, i, j)
            eps = epsilon(A, B, fNum)
            if eps < optimal[0]:
                optimal[0] = eps
                optimal[1] = i
                optimal[2] = j

print(optimal)

drawGraphs(fNum, num, optimal[1], optimal[2])
