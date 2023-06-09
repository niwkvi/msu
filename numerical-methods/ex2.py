from math import sqrt


def func1(a, b, px, qx, fx, alpha0, alpha1, A, beta0, beta1, B, n):
    n1, n2 = n, 2 * n
    h1, h2 = (b - a) / n1, (b - a) / n2
    alpha01, alpha11 = alpha0 - alpha1 / h1, alpha1 / h1
    alpha02, alpha12 = alpha0 - alpha1 / h2, alpha1 / h2
    beta01, beta11 = -beta1 / h1, beta0 + beta1 / h1
    beta02, beta12 = -beta1 / h2, beta0 + beta1 / h2

    a1, a2 = [0], [0]
    b1, b2 = [alpha01], [alpha02]
    c1, c2 = [alpha11], [alpha12]
    d1, d2 = [A], [A]

    for i in range(n1 - 1):
        xi = a + i * h1
        a1.append(1 / h1 ** 2)
        b1.append(qx(xi) - px(xi) / h1 - 2 / h1 ** 2)
        c1.append(1 / h1 ** 2 + px(xi) / h1)
        d1.append(fx(xi))

    for i in range(n2 - 1):
        xi = a + i * h2
        a2.append(1 / h2 ** 2)
        b2.append(qx(xi) - px(xi) / h2 - 2 / h2 ** 2)
        c2.append(1 / h2 ** 2 + px(xi) / h2)
        d2.append(fx(xi))

    a1.append(beta01)
    a2.append(beta02)
    b1.append(beta11)
    b2.append(beta12)
    c1.append(0)
    c2.append(0)
    d1.append(B)
    d2.append(B)

    ans1 = solve_threediagonal_matrix(a1, b1, c1, d1)
    ans2 = solve_threediagonal_matrix(a2, b2, c2, d2)
    print(ans1)
    print(ans2)

    diff = 0
    for i in range(n1 + 1):
        diff += (ans2[2 * i] - ans1[i]) ** 2
    diff = sqrt(diff)
    print(diff)


def solve_threediagonal_matrix(a, b, c, d):
    n = len(d) - 1
    y = [b[0]]
    alpha = [-c[0] / y[0]]
    beta = [d[0] / y[0]]

    for i in range(1, n):
        y.append(b[i] + a[i] * alpha[i - 1])
        alpha.append(-c[i] / y[i])
        beta.append((d[i] - a[i] * beta[i - 1]) / y[i])
    y.append(b[n] + a[n] * alpha[n - 1])
    beta.append((d[n] - a[n] * beta[n - 1]) / y[n])

    x = [beta[n]]
    for i in range(n - 1, -1, -1):
        x.append(alpha[i] * x[n - i - 1] + beta[i])
    x.reverse()
    return x


# x^2y''+2xy'=1/x
# y''+(2/x)y'=1/x^3

# y' = (y_i+1 - y_i-1) / 2h
# y" = (y_i+1 - 2y_i + y_i-1) / h^2

func1(1, 2.7182, lambda x: 2 / x, lambda x: 0, lambda x: 1 / (x ** 3), 2.5, 0, 1, 2.5, 0, -15.7955, 1000000)
