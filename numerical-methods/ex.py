import numpy as np


def f(x):
    return (x ** 4) / np.log(x)


def gauss(a, b, n, f):
    h = (b - a) / n
    x = np.arange(a, b, h) + h / 2

    c1 = (18 - 30 ** 0.5) / 36
    c2 = (18 + 30 ** 0.5) / 36

    values = (c1 * f(x - h / 2 * ((15 + 2 * 30 ** 0.5) / 35) ** 0.5) +
              c2 * f(x - h / 2 * ((15 - 2 * 30 ** 0.5) / 35) ** 0.5) +
              c2 * f(x + h / 2 * ((15 - 2 * 30 ** 0.5) / 35) ** 0.5) +
              c1 * f(x + h / 2 * ((15 + 2 * 30 ** 0.5) / 35) ** 0.5))

    return np.sum(values) * h / 2


def eps(f):
    results = []
    a, b = 0.0000001, 0.99999999999999999
    for i in range(100000, 100004):
        result = gauss(a, b, 10 * (1 + i), f)
        results.append(result)
    for result in results:
        print(result)
    print()
    for result1, result2 in zip(results[:-1], results[1:]):
        print(abs(result1 - result2))


eps(f)
