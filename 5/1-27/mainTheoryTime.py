import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data1 = pd.read_csv('table1.csv', delimiter=',')
data2 = pd.read_csv('table2.csv', delimiter=',')

plt.plot(data1['size'], data1['time'] / (data1['size'] * data1['size'] + data1['edges']), color='red')
plt.plot(data2['size'], data2['time'] / (data2['edges'] * np.log(data2['size'])), color='green')
plt.show()
