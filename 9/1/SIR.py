import matplotlib.pyplot as plt


S, I, R, t = [460], [12], [0], [0]
# S, I, R, t = [382], [15], [0], [0]
# S, I, R, t = [4360000], [1378], [0], [0]
dt = 1
# beta, mu = 0.000318, 0.0175
beta, mu = 0.0004, 0.018

for i in range(90):
    STemp = (-beta * I[i] * S[i]) * dt + S[i]
    ITemp = (beta * I[i] * S[i] - mu * I[i]) * dt + I[i]
    RTemp = mu * I[i] * dt + R[i]
    S.append(STemp)
    I.append(ITemp)
    R.append(RTemp)
    t.append(t[i] + dt)

plt.subplots()
plt.plot(t, S, color='blue')
plt.plot(t, I, color='red')
plt.plot(t, R, color='green')
plt.show()
