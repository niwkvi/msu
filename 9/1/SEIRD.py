import matplotlib.pyplot as plt


S, E, I, R, D, t = [10000], [100], [100], [0], [0], [0]
dt = 0.001
beta, sigma, gamma, mu = 10, 1, 0.5, 0.02

for i in range(10000):
    N = S[i] + E[i] + I[i] + R[i]
    STemp = - beta * S[i] * I[i] / N * dt + S[i]
    ETemp = (beta * S[i] * I[i] / N - sigma * E[i]) * dt + E[i]
    ITemp = (sigma * E[i] - gamma * I[i] - mu * I[i]) * dt + I[i]
    RTemp = gamma * I[i] * dt + R[i]
    DTemp = mu * I[i] * dt + D[i]
    S.append(STemp)
    E.append(ETemp)
    I.append(ITemp)
    R.append(RTemp)
    D.append(DTemp)
    t.append(t[i] + dt)

plt.subplots()
plt.plot(t, S, color='blue')
plt.plot(t, E, color='orange')
plt.plot(t, I, color='red')
plt.plot(t, R, color='green')
plt.plot(t, D, color='black')
plt.show()
