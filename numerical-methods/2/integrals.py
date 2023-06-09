import numpy as np

eps = 0.00001


def f(x):
    return (2 * x + 0.5) * np.sin(x)


def F(x):
    pass


def trapezoid(func, a, b, n):
    h = (b - a) / n
    x = np.arange(a, b + eps, h)

    values = func(x)
    values[0] /= 2
    values[-1] /= 2

    return np.sum(values) * h


def rectangles(func, a, b, n):
    h = (b - a) / n
    x = np.arange(a, b, h) + h / 2

    values = func(x)

    return np.sum(values) * h


def simpson(func, a, b, n):
    h = 2 * (b - a) / n
    x = np.arange(a, b, h)

    values = func(x) + 4 * func(x + h / 2) + func(x + h)

    return np.sum(values) * h / 6


def threeEights(func, a, b, n):
    h = (b - a) / n
    x = np.arange(a, b, h)

    values = func(x) + 3 * func((3 * x + h) / 3) + 3 * func((3 * x + h) / 3) + func(x + h)

    return np.sum(values) * h / 8


def gauss1(func, a, b, n):
    h = (b - a) / n
    x = np.arange(a, b, h) + h / 2

    c1 = (18 - 30 ** 0.5) / 36
    c2 = (18 + 30 ** 0.5) / 36

    values = (c1 * func(x + h / 2 * ((15 + 2 * 30 ** 0.5) / 35) ** 0.5) +
              c2 * func(x - h / 2 * ((15 + 2 * 30 ** 0.5) / 35) ** 0.5) +
              c2 * func(x + h / 2 * ((15 - 2 * 30 ** 0.5) / 35) ** 0.5) +
              c1 * func(x - h / 2 * ((15 - 2 * 30 ** 0.5) / 35) ** 0.5))

    return np.sum(values) * h / 2


def gauss(func, a, b, n):
    h = (b - a) / n
    x = np.arange(a, b, h) + h / 2

    c1 = (18 - 30 ** 0.5) / 36
    c2 = (18 + 30 ** 0.5) / 36

    values = (c1 * func(x + h / 2 * ((15 + 2 * 30 ** 0.5) / 35) ** 0.5) +
              c2 * func(x - h / 2 * ((15 + 2 * 30 ** 0.5) / 35) ** 0.5) +
              c2 * func(x + h / 2 * ((15 - 2 * 30 ** 0.5) / 35) ** 0.5) +
              c1 * func(x - h / 2 * ((15 - 2 * 30 ** 0.5) / 35) ** 0.5))

    return np.sum(values) * h / 2


A, B = 1, 2
N = 5

for i in range(5, 100000):
    ans = simpson(f, A, B, i)
    print(ans)
