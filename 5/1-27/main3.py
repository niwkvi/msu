import matplotlib.pyplot as plt
import pandas as pd

data1 = pd.read_csv('table1.csv', delimiter=',')
data2 = pd.read_csv('table2.csv', delimiter=',')

plt.plot(data1['size'], data1['avgTime'], color='red')
plt.plot(data2['size'], data2['avgTime'], color='green')
plt.show()
