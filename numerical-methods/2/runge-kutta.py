import numpy as np

funcs = np.array([

    # 1(1) - 7(a)

    {'f': lambda x, y: np.array([y[0] / x + x * np.sin(x)]),
     'area': np.array([np.pi / 2, np.pi / 2 + 5]),
     'init': np.array([1]),
     'y': lambda x: np.array([2 * x / np.pi - x * np.cos(x)])},

    # 1(2) - 7(b)

    {'f': lambda x, y: np.array([(y[0] ** 2 * np.log(x)) / (3 * x) - y[0] / x]),
     'area': np.array([1, 6]),
     'init': np.array([3]),
     'y': lambda x: np.array([3 / (np.log(x) + 1)])},

    # 2 - 839
    {'f': lambda t, x: np.array([2 * x[0] - 3 * x[1],
                                 x[0] - 2 * x[1] + 2 * np.sin(t)]),
     'area': np.array([0, 5]),
     'init': np.array([1, 2]),
     'y': lambda t: np.array([-3 * np.exp(t) + 4 * np.exp(-t) + 3 * np.sin(t),
                              -np.exp(t) + 4 * np.exp(-t) + 2 * np.sin(t) - np.cos(t)])},

    # 3(1)
    {'f': lambda t, x: np.array([2 * t * x[0] * x[3],
                                 10 * t * x[0] ** 5 * x[3],
                                 2 * t * x[3],
                                 -2 * t * (x[2] - 1)]),
     'area': np.array([0, 10]),
     'init': np.array([1, 1, 1, 1]),
     'y': lambda t: np.array([np.exp(np.sin(t ** 2)),
                              np.exp(5 * np.sin(t ** 2)),
                              np.sin(t ** 2) + 1,
                              np.cos(t ** 2)])},

    # 3(2)
    {'f': lambda x, y: np.array([y[0] * (1 / x - 2 * x - x / np.sqrt(1 + x ** 2)) /
                                 (np.sqrt(1 + x ** 2) + x ** 2 - np.log(x))]),
     'area': np.array([1, 6]),
     'init': np.array([2]),
     'y': lambda t: np.array([2 * (2 ** 0.5 + 1) / (np.sqrt(1 + t ** 2) + t ** 2 - np.log(t))])}

])


def RK1(func, n):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    for j in range(1, n + 1):
        X[j] = X[j - 1] + func['f'](T[j - 1], X[j - 1]) * h

    return T, X


def RK2(func, n, c2):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + h / (2 * c2), X[j - 1] + k1 / (2 * c2))
        X[j] = X[j - 1] + k1 * (1 - c2) + k2 * c2

    return T, X


def RK3_1(func, n, a2, a3):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    b32 = a3 * (a2 - a3) / (a2 * (3 * a2 - 2))
    b31 = a3 - b32
    c2 = (3 * a3 - 2) / (6 * a2 * (a3 - a2))
    c3 = (3 * a2 - 2) / (6 * a3 * (a2 - a3))
    c1 = 1 - c2 - c3

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + a2 * h, X[j - 1] + a2 * k1) * h
        k3 = func['f'](T[j - 1] + a3 * h, X[j - 1] + b31 * k1 + b32 * k2) * h

        X[j] = X[j - 1] + k1 * c1 + k2 * c2 + k3 * c3

    return T, X


def RK3_2(func, n, b32):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    c3 = 1 / (4 * b32)
    c2 = 3 / 4 - c3
    c1 = 1 - c2 - c3
    b31 = 2 / 3 - b32

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + 2 / 3 * h, X[j - 1] + 2 / 3 * k1) * h
        k3 = func['f'](T[j - 1] + 2 / 3 * h, X[j - 1] + b31 * k1 + b32 * k2) * h

        X[j] = X[j - 1] + k1 * c1 + k2 * c2 + k3 * c3

    return T, X


def RK3_3(func, n, c3):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    b32 = 1 / (4 * c3)
    c1 = 1 / 4 - c3

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + 2 / 3 * h, X[j - 1] + 2 / 3 * k1) * h
        k3 = func['f'](T[j - 1], X[j - 1] - b32 * k1 + b32 * k2) * h

        X[j] = X[j - 1] + k1 * c1 + k2 * 3 / 4 + k3 * c3

    return T, X


def RK4_1(func, n, a2, a3):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    c2 = (2 * a3 - 1) / (12 * a2 * (a2 - a3) * (a2 - 1))
    c3 = (2 * a2 - 1) / (12 * a3 * (a3 - a2) * (a3 - 1))
    c4 = (4 * a2 - 6 * a2 * a3 + 4 * a3 - 3) / (12 * (a2 - 1) * (1 - a3))
    c1 = 1 - c2 - c3 - c4
    b43 = c3 * (1 - a3) / c4
    b32 = 1 / (24 * a2 * c3 * (1 - a3))
    b42 = (1 / 6 - b43 * a3 * c4 - a2 * c3 * b32) / (a2 * c4)
    b31 = a3 - b32
    b41 = 1 - b42 - b43

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + a2 * h, X[j - 1] + a2 * k1) * h
        k3 = func['f'](T[j - 1] + a3 * h, X[j - 1] + b31 * k1 + b32 * k2) * h
        k4 = func['f'](T[j - 1] + h, X[j - 1] + b41 * k1 + b42 * k2 + b43 * k3) * h

        X[j] = X[j - 1] + c1 * k1 + c2 * k2 + c3 * k3 + c4 * k4

    return T, X


def RK4_2(func, n, c3):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    c1 = 1 / 6 - c3
    b32 = 1 / (12 * c3)
    b31 = -b32
    b43 = 6 * c3
    b41 = -1 / 2 - b43

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + h / 2, X[j - 1] + k1 / 2) * h
        k3 = func['f'](T[j - 1], X[j - 1] + b31 * k1 + b32 * k2) * h
        k4 = func['f'](T[j - 1] + h, X[j - 1] + b41 * k1 + 3 / 2 * k2 + k3 * b43) * h

        X[j] = X[j - 1] + c1 * k1 + 2 / 3 * k2 + c3 * k3 + k4 / 6

    return T, X


def RK4_3(func, n, c3):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    c2 = 2 / 3 - c3
    b32 = 1 / (6 * c3)
    b43 = 3 * c3
    b42 = 1 - 3 * c3
    b31 = 1 / 2 - b32

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + h / 2, X[j - 1] + k1 / 2) * h
        k3 = func['f'](T[j - 1] + h / 2, X[j - 1] + b31 * k1 + b32 * k2) * h
        k4 = func['f'](T[j - 1] + h, X[j - 1] + b42 * k2 + b43 * k3) * h

        X[j] = X[j - 1] + k1 / 6 + c2 * k2 + c3 * k3 + k4 / 6

    return T, X


def RK4_4(func, n, c4):
    h = (func['area'][1] - func['area'][0]) / n
    T = np.linspace(func['area'][0], func['area'][1], n + 1)
    X = np.empty((n + 1, len(func['init'])))
    X[0] = func['init']

    c2 = 1 / 6 - c4
    b43 = 1 / (3 * c4)
    b42 = -1 / (12 * c4)
    b41 = 1 - 1 / (4 * c4)

    for j in range(1, n + 1):
        k1 = func['f'](T[j - 1], X[j - 1]) * h
        k2 = func['f'](T[j - 1] + h, X[j - 1] + k1) * h
        k3 = func['f'](T[j - 1] + h / 2, X[j - 1] + 3 / 8 * k1 + k2 / 8) * h
        k4 = func['f'](T[j - 1] + h, X[j - 1] + b41 * k1 + b42 * k2 + b43 * k3) * h

        X[j] = X[j - 1] + k1 / 6 + c2 * k2 + 2 / 3 * k3 + c4 * k4

    return T, X


def epsilon_0(func, n, method):
    epsilon = np.inf

    T, X = method(func, n)
    total = np.sqrt(np.sum((X - np.transpose(func['y'](T))) ** 2)) / n
    if total < epsilon:
        epsilon = total

    return [epsilon]


def epsilon_1(func, n, method):
    epsilon = np.inf
    param1 = -np.inf

    for i in np.arange(-2, 5, 0.1):
        T, X = method(func, n, i)
        total = np.sqrt(np.sum((X - np.transpose(func['y'](T))) ** 2)) / n
        if total < epsilon:
            epsilon, param1 = total, i

    return [param1, epsilon]


def epsilon_2(func, n, method):
    epsilon = np.inf
    param1, param2 = -np.inf, -np.inf

    for i in np.arange(-2, 5, 0.1):
        for j in np.arange(-2, 5, 0.1):
            T, X = method(func, n, i, j)
            total = np.sqrt(np.sum((X - np.transpose(func['y'](T))) ** 2)) / n
            if total < epsilon:
                epsilon, param1, param2 = total, i, j

    return [param1, param2, epsilon]


ns = [10, 50, 100]
funcNum = 0

for k in ns:
    print(epsilon_0(funcs[funcNum], k, RK1))
