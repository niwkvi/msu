import matplotlib.pyplot as plt
import pandas as pd

data1 = pd.read_csv('table1.csv', delimiter=',')
data2 = pd.read_csv('table2.csv', delimiter=',')

plt.plot(0, 0)
plt.plot(data1['steps'], data1['time'], color='red')
plt.plot(data2['steps'], data2['time'], color='green')
plt.savefig('table.png')
plt.show()
