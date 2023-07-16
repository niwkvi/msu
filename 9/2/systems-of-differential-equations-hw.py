import numpy as np
import matplotlib.pyplot as plt


systems = [
    (
        lambda x1, x2, x3, t: x1 + 2 * x2 - 3 * x3 + np.sin(t),
        lambda x1, x2, x3, t: -3 * x1 + x2 + 2 * x3 - np.cos(t),
        lambda x1, x2, x3, t: 2 * x1 - 3 * x2 + x3 - np.sin(t) * np.cos(t)
    )
]

answers = [

]

inits = [
    (0, 1, -1)
]

intervals = [
    (0, 10)
]

ns = [10, 50, 100]


def euler(i, n):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    for j in range(1, len(T)):
        X[j] = X[j - 1] + systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        Y[j] = Y[j - 1] + systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        Z[j] = Z[j - 1] + systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

    return T, X, Y, Z


def runge2(i, n, c):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k13 = systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + k11 / (2 * c), Y[j - 1] + k12 / (2 * c), Z[j - 1] + k13 / (2 * c),
                            T[j - 1] + h / (2 * c)) * h
        k22 = systems[i][1](X[j - 1] + k11 / (2 * c), Y[j - 1] + k12 / (2 * c), Z[j - 1] + k13 / (2 * c),
                            T[j - 1] + h / (2 * c)) * h
        k23 = systems[i][2](X[j - 1] + k11 / (2 * c), Y[j - 1] + k12 / (2 * c), Z[j - 1] + k13 / (2 * c),
                            T[j - 1] + h / (2 * c)) * h

        X[j] = X[j - 1] + k11 * (1 - c) + k21 * c
        Y[j] = Y[j - 1] + k12 * (1 - c) + k22 * c
        Z[j] = Z[j - 1] + k13 * (1 - c) + k23 * c

    return T, X, Y, Z


def runge3_1(i, n, a2, a3):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    b32 = a3 * (a2 - a3) / (a2 * (3 * a2 - 2))
    b31 = a3 - b32
    c2 = (3 * a3 - 2) / (6 * a2 * (a3 - a2))
    c3 = (3 * a2 - 2) / (6 * a3 * (a2 - a3))
    c1 = 1 - c2 - c3

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k13 = systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + a2 * k11, Y[j - 1] + a2 * k12, Z[j - 1] + a2 * k13,
                            T[j - 1] + a2 * h) * h
        k22 = systems[i][1](X[j - 1] + a2 * k11, Y[j - 1] + a2 * k12, Z[j - 1] + a2 * k13,
                            T[j - 1] + a2 * h) * h
        k23 = systems[i][2](X[j - 1] + a2 * k11, Y[j - 1] + a2 * k12, Z[j - 1] + a2 * k13,
                            T[j - 1] + a2 * h) * h

        k31 = systems[i][0](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + a3 * h) * h
        k32 = systems[i][1](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + a3 * h) * h
        k33 = systems[i][2](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + a3 * h) * h

        X[j] = X[j - 1] + k11 * c1 + k21 * c2 + k31 * c3
        Y[j] = Y[j - 1] + k12 * c1 + k22 * c2 + k32 * c3
        Z[j] = Z[j - 1] + k13 * c1 + k23 * c2 + k33 * c3

    return T, X, Y, Z


def runge3_2(i, n, b32):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    c3 = 1 / (4 * b32)
    c2 = 3/4 - c3
    c1 = 1 - c2 - c3
    b31 = 2/3 - b32

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k13 = systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + 2/3 * k11, Y[j - 1] + 2/3 * k12, Z[j - 1] + 2/3 * k13,
                            T[j - 1] + 2/3 * h) * h
        k22 = systems[i][1](X[j - 1] + 2/3 * k11, Y[j - 1] + 2/3 * k12, Z[j - 1] + 2/3 * k13,
                            T[j - 1] + 2/3 * h) * h
        k23 = systems[i][2](X[j - 1] + 2/3 * k11, Y[j - 1] + 2/3 * k12, Z[j - 1] + 2/3 * k13,
                            T[j - 1] + 2/3 * h) * h

        k31 = systems[i][0](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + 2/3 * h) * h
        k32 = systems[i][1](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + 2/3 * h) * h
        k33 = systems[i][2](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + 2/3 * h) * h

        X[j] = X[j - 1] + k11 * c1 + k21 * c2 + k31 * c3
        Y[j] = Y[j - 1] + k12 * c1 + k22 * c2 + k32 * c3
        Z[j] = Z[j - 1] + k13 * c1 + k23 * c2 + k33 * c3

    return T, X, Y, Z


def runge4_1(i, n, a2, a3):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    c2 = (2 * a3 - 1) / (12 * a2 * (a2 - a3) * (a2 - 1))
    c3 = (2 * a2 - 1) / (12 * a3 * (a3 - a2) * (a3 - 1))
    c4 = (4 * a2 - 6 * a2 * a3 + 4 * a3 - 3) / (12 * (a2 - 1) * (1 - a3))
    c1 = 1 - c2 - c3 - c4
    b43 = c3 * (1 - a3) / c4
    b32 = 1 / (24 * a2 * c3 * (1 - a3))
    b42 = (1 / 6 - b43 * a3 * c4 - a2 * c3 * b32) / (a2 * c4)
    b31 = a3 - b32
    b41 = 1 - b42 - b43

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k13 = systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + a2 * k11, Y[j - 1] + a2 * k12, Z[j - 1] + a2 * k13,
                            T[j - 1] + a2 * h) * h
        k22 = systems[i][1](X[j - 1] + a2 * k11, Y[j - 1] + a2 * k12, Z[j - 1] + a2 * k13,
                            T[j - 1] + a2 * h) * h
        k23 = systems[i][2](X[j - 1] + a2 * k11, Y[j - 1] + a2 * k12, Z[j - 1] + a2 * k13,
                            T[j - 1] + a2 * h) * h

        k31 = systems[i][0](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + a3 * h) * h
        k32 = systems[i][1](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + a3 * h) * h
        k33 = systems[i][2](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + a3 * h) * h

        k41 = systems[i][0](X[j - 1] + b41 * k11 + b42 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + b42 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + b42 * k23 + b43 * k33, T[j - 1] + h) * h
        k42 = systems[i][1](X[j - 1] + b41 * k11 + b42 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + b42 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + b42 * k23 + b43 * k33, T[j - 1] + h) * h
        k43 = systems[i][2](X[j - 1] + b41 * k11 + b42 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + b42 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + b42 * k23 + b43 * k33, T[j - 1] + h) * h

        X[j] = X[j - 1] + k11 * c1 + k21 * c2 + k31 * c3 + k41 * c4
        Y[j] = Y[j - 1] + k12 * c1 + k22 * c2 + k32 * c3 + k42 * c4
        Z[j] = Z[j - 1] + k13 * c1 + k23 * c2 + k33 * c3 + k43 * c4

    return T, X, Y, Z


def runge4_2(i, n, c3):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    c1 = 1/6 - c3
    b32 = 1 / (12 * c3)
    b31 = -b32
    b43 = 6 * c3
    b41 = -1/2 - b43

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k13 = systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + k11 / 2, Y[j - 1] + k12 / 2, Z[j - 1] + k13 / 2,
                            T[j - 1] + h / 2) * h
        k22 = systems[i][1](X[j - 1] + k11 / 2, Y[j - 1] + k12 / 2, Z[j - 1] + k13 / 2,
                            T[j - 1] + h / 2) * h
        k23 = systems[i][2](X[j - 1] + k11 / 2, Y[j - 1] + k12 / 2, Z[j - 1] + k13 / 2,
                            T[j - 1] + h / 2) * h

        k31 = systems[i][0](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1]) * h
        k32 = systems[i][1](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1]) * h
        k33 = systems[i][2](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1]) * h

        k41 = systems[i][0](X[j - 1] + b41 * k11 + 3/2 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + 3/2 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + 3/2 * k23 + b43 * k33, T[j - 1] + h) * h
        k42 = systems[i][1](X[j - 1] + b41 * k11 + 3/2 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + 3/2 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + 3/2 * k23 + b43 * k33, T[j - 1] + h) * h
        k43 = systems[i][2](X[j - 1] + b41 * k11 + 3/2 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + 3/2 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + 3/2 * k23 + b43 * k33, T[j - 1] + h) * h

        X[j] = X[j - 1] + k11 * c1 + k21 * 2/3 + k31 * c3 + k41 / 6
        Y[j] = Y[j - 1] + k12 * c1 + k22 * 2/3 + k32 * c3 + k42 / 6
        Z[j] = Z[j - 1] + k13 * c1 + k23 * 2/3 + k33 * c3 + k43 / 6

    return T, X, Y, Z


def runge4_3(i, n, c3):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    c2 = 2/3 - c3
    b32 = 1 / (6 * c3)
    b43 = 3 * c3
    b42 = 1 - 3 * c3
    b31 = 1/2 - b32

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k13 = systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + k11 / 2, Y[j - 1] + k12 / 2, Z[j - 1] + k13 / 2,
                            T[j - 1] + h / 2) * h
        k22 = systems[i][1](X[j - 1] + k11 / 2, Y[j - 1] + k12 / 2, Z[j - 1] + k13 / 2,
                            T[j - 1] + h / 2) * h
        k23 = systems[i][2](X[j - 1] + k11 / 2, Y[j - 1] + k12 / 2, Z[j - 1] + k13 / 2,
                            T[j - 1] + h / 2) * h

        k31 = systems[i][0](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + h / 2) * h
        k32 = systems[i][1](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + h / 2) * h
        k33 = systems[i][2](X[j - 1] + b31 * k11 + b32 * k21, Y[j - 1] + b31 * k12 + b32 * k22,
                            Z[j - 1] + b31 * k13 + b32 * k23, T[j - 1] + h / 2) * h

        k41 = systems[i][0](X[j - 1] + b42 * k21 + b43 * k31, Y[j - 1] + b42 * k22 + b43 * k32,
                            Z[j - 1] + b42 * k23 + b43 * k33, T[j - 1] + h) * h
        k42 = systems[i][1](X[j - 1] + b42 * k21 + b43 * k31, Y[j - 1] + b42 * k22 + b43 * k32,
                            Z[j - 1] + b42 * k23 + b43 * k33, T[j - 1] + h) * h
        k43 = systems[i][2](X[j - 1] + b42 * k21 + b43 * k31, Y[j - 1] + b42 * k22 + b43 * k32,
                            Z[j - 1] + b42 * k23 + b43 * k33, T[j - 1] + h) * h

        X[j] = X[j - 1] + k11 / 6 + k21 * c2 + k31 * c3 + k41 / 6
        Y[j] = Y[j - 1] + k12 / 6 + k22 * c2 + k32 * c3 + k42 / 6
        Z[j] = Z[j - 1] + k13 / 6 + k23 * c2 + k33 * c3 + k43 / 6

    return T, X, Y, Z


def runge4_4(i, n, c4):
    h = (intervals[i][1] - intervals[i][0]) / n
    T = np.linspace(intervals[i][0], intervals[i][1], n + 1)
    X, Y, Z = np.empty_like(T), np.empty_like(T), np.empty_like(T)
    X[0], Y[0], Z[0] = inits[i][0], inits[i][1], inits[i][2]

    c2 = 1/6 - c4
    b43 = 1 / (3 * c4)
    b42 = -1 / (12 * c4)
    b41 = 1 - 1 / (4 * c4)

    for j in range(1, len(T)):
        k11 = systems[i][0](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k12 = systems[i][1](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h
        k13 = systems[i][2](X[j - 1], Y[j - 1], Z[j - 1], T[j - 1]) * h

        k21 = systems[i][0](X[j - 1] + k11, Y[j - 1] + k12, Z[j - 1] + k13,
                            T[j - 1] + h) * h
        k22 = systems[i][1](X[j - 1] + k11, Y[j - 1] + k12, Z[j - 1] + k13,
                            T[j - 1] + h) * h
        k23 = systems[i][2](X[j - 1] + k11, Y[j - 1] + k12, Z[j - 1] + k13,
                            T[j - 1] + h) * h

        k31 = systems[i][0](X[j - 1] + 3/8 * k11 + k21 / 8, Y[j - 1] + 3/8 * k12 + k22 / 8,
                            Z[j - 1] + 3/8 * k13 + k23 / 8, T[j - 1] + h / 2) * h
        k32 = systems[i][1](X[j - 1] + 3/8 * k11 + k21 / 8, Y[j - 1] + 3/8 * k12 + k22 / 8,
                            Z[j - 1] + 3/8 * k13 + k23 / 8, T[j - 1] + h / 2) * h
        k33 = systems[i][2](X[j - 1] + 3/8 * k11 + k21 / 8, Y[j - 1] + 3/8 * k12 + k22 / 8,
                            Z[j - 1] + 3/8 * k13 + k23 / 8, T[j - 1] + h / 2) * h

        k41 = systems[i][0](X[j - 1] + b41 * k11 + b42 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + b42 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + b42 * k23 + b43 * k33, T[j - 1] + h) * h
        k42 = systems[i][1](X[j - 1] + b41 * k11 + b42 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + b42 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + b42 * k23 + b43 * k33, T[j - 1] + h) * h
        k43 = systems[i][2](X[j - 1] + b41 * k11 + b42 * k21 + b43 * k31,
                            Y[j - 1] + b41 * k12 + b42 * k22 + b43 * k32,
                            Z[j - 1] + b41 * k13 + b42 * k23 + b43 * k33, T[j - 1] + h) * h

        X[j] = X[j - 1] + k11 / 6 + k21 * c2 + k31 * 2/3 + k41 * c4
        Y[j] = Y[j - 1] + k12 / 6 + k22 * c2 + k32 * 2/3 + k42 * c4
        Z[j] = Z[j - 1] + k13 / 6 + k23 * c2 + k33 * 2/3 + k43 * c4

    return T, X, Y, Z


def drawGraphs(i, n, p1, p2):
    T, X, Y, Z = runge4_4(i, n, p1)
    plt.plot(X, Y, Z, color='red')
    plt.show()


fNum = 0
n = 100
drawGraphs(fNum, n, 0.1, 0.2)
