from math import *
import numpy as np


fs = [
    lambda x, y: y - x ** 2,

    lambda x, y: (2 * x - sin(x)) / y,
    lambda x, y: -40 * (y - 1) ** 2 * sin(100 * x),
    lambda x, y: y / 8 - sin(48 * x) / y,

    lambda x, y: (1 - 2 * x * y) / (x * (x - 1)),
    lambda x, y: (x * sqrt(y - x ** 2) + 2 * y) / x,
    lambda x, y: (y ** 3 / tan(x) - x ** 2 * sin(x) ** 3) / (y ** 2),
    lambda x, y: (-(y ** 2) + 2 * x * y - 1) / (x ** 2 - 1),

    lambda x, y: 50 * sqrt(1 - y * sin(50 * x)) if 1 >= y * sin(50 * x) else inf
]

ys = [
    lambda x: x ** 2 + 2 * x - exp(x) + 2,

    lambda x: sqrt(2 * x * x + 2 * cos(x) - 1),
    lambda x: (2 * cos(100 * x) - 12) / (2 * cos(100 * x) - 7),
    lambda x: sqrt((1781.85 * exp(x / 4) + 8 * (sin(48 * x) + 192 * cos(48 * x))) / 36865),

    lambda x: (x - log(x) + log(2) - 1) / ((x - 1) ** 2),
    lambda x: x ** 2 + x ** 4 / 4 * log(exp(2 * sqrt(e - 1)) * x) ** 2,
    lambda x: (27 / sin(1) ** 9 + 1 - x ** 3) ** (1 / 3) * sin(x) ** 3,
    lambda x: x + 2 / log(exp(-2 / 1.1) / 19 * (1 - x) / (1 + x)),

    lambda x: sin(50 * x)
]

intervals = [(0, 10),
             (0, 10), (0, 10), (0, 10),
             (2, 50), (1, 50), (1, 3), (-0.9, 0.9),
             (0, 10 * pi)]

inits = [1,
         1, 2, 0.3,
         1, e, 3, -2,
         0]


def runge1():

    pass


def runge2():
    pass


def runge3():
    pass


def runge4_1(i, n, a2, a3):
    h = (intervals[i][1] - intervals[i][0]) / n
    X = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    Y = np.empty_like(X)
    Y[0] = inits[i]

    c2 = (2 * a3 - 1) / (12 * a2 * (a2 - a3) * (a2 - 1))
    c3 = (2 * a2 - 1) / (12 * a3 * (a3 - a2) * (a3 - 1))
    c4 = (4 * a2 - 6 * a2 * a3 + 4 * a3 - 3) / (12 * (a2 - 1) * (1 - a3))
    c1 = 1 - c2 - c3 - c4
    b21 = a2
    b43 = c3 * (1 - a3) / c4
    b32 = 1 / (24 * a2 * c3 * (1 - a3))
    b42 = (1/6 - b43 * a3 * c4 - a2 * c3 * b32) / (a2 * c4)
    b31 = a3 - b32
    b41 = 1 - b42 - b43

    for j in range(1, len(X)):
        k1 = fs[i](X[j - 1], Y[j - 1]) * h
        k2 = fs[i](X[j - 1] + a2 * h, Y[j - 1] + b21 * k1) * h
        k3 = fs[i](X[j - 1] + a3 * h, Y[j - 1] + b31 * k1 + b32 * k2) * h
        k4 = fs[i](X[j - 1] + h, Y[j - 1] + b41 * k1 + b42 * k2 + b43 * k3) * h

        Y[j] = Y[j-1] + c1 * k1 + c2 * k2 + c3 * k3 + c4 * k4

    return X, Y


def runge4_2(i, n, c3):
    h = (intervals[i][1] - intervals[i][0]) / n
    X = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    Y = np.empty_like(X)
    Y[0] = inits[i]

    c1 = 1 / 6 - c3
    b32 = 1 / (12 * c3)
    b31 = -b32
    b43 = 6 * c3
    b41 = -1 / 2 - b43

    for j in range(1, len(X)):
        k1 = fs[i](X[j - 1], Y[j - 1]) * h
        k2 = fs[i](X[j - 1] + h / 2, Y[j - 1] + k1 / 2) * h
        k3 = fs[i](X[j - 1], Y[j - 1] + b31 * k1 + b32 * k2) * h
        k4 = fs[i](X[j - 1] + h, Y[j - 1] + b41 * k1 + 3 / 2 * k2 + k3 * b43) * h

        Y[j] = Y[j - 1] + c1 * k1 + 2 / 3 * k2 + c3 * k3 + k4 / 6

    return X, Y


def runge4_3(i, n, c3):
    h = (intervals[i][1] - intervals[i][0]) / n
    X = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    Y = np.empty_like(X)
    Y[0] = inits[i]

    c2 = 2 / 3 - c3
    b32 = 1 / (6 * c3)
    b43 = 3 * c3
    b42 = 1 - 3 * c3
    b31 = 1 / 2 - b32

    for j in range(1, len(X)):
        k1 = fs[i](X[j - 1], Y[j - 1]) * h
        k2 = fs[i](X[j - 1] + h / 2, Y[j - 1] + k1 / 2) * h
        k3 = fs[i](X[j - 1] + h / 2, Y[j - 1] + b31 * k1 + b32 * k2) * h
        k4 = fs[i](X[j - 1] + h, Y[j - 1] + b42 * k2 + b43 * k3) * h

        Y[j] = Y[j - 1] + k1 / 6 + c2 * k2 + c3 * k3 + k4 / 6

    return X, Y


def runge4_4(i, n, c4):
    h = (intervals[i][1] - intervals[i][0]) / n
    X = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    Y = np.empty_like(X)
    Y[0] = inits[i]

    c2 = 1/6 - c4
    b43 = 1 / (3 * c4)
    b42 = -1 / (12 * c4)
    b41 = 1 - 1 / (4 * c4)

    for j in range(1, len(X)):
        k1 = fs[i](X[j - 1], Y[j - 1]) * h
        k2 = fs[i](X[j - 1] + h, Y[j - 1] + k1) * h
        k3 = fs[i](X[j - 1] + h / 2, Y[j - 1] + 3 / 8 * k1 + k2 / 8) * h
        k4 = fs[i](X[j - 1] + h, Y[j - 1] + b41 * k1 + b42 * k2 + b43 * k3) * h

        Y[j] = Y[j - 1] + k1 / 6 + c2 * k2 + 2 / 3 * k3 + c4 * k4

    return X, Y


def epsilon(X, Y, i):
    s = 0
    for j in range(len(X)):
        s += ((Y[j] - ys[i](X[j])) ** 2) / (len(X) ** 2)
    return sqrt(s)


fNum = 8
num = 100
optimal = [100, 0]

for i in np.arange(-3, 3, 0.1):
    A, B = runge4_4(fNum, num, i)
    eps = epsilon(A, B, fNum)
    if eps < optimal[0]:
        optimal[0] = eps
        optimal[1] = i

print(optimal)
