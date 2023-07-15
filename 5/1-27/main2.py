import matplotlib.pyplot as plt
import pandas as pd


data1 = pd.read_csv('C:/Users/Gondolin/CLionProjects/27/table1.csv', delimiter=',')
data2 = pd.read_csv('C:/Users/Gondolin/CLionProjects/27/table2.csv', delimiter=',')

plt.plot(0, 0)
plt.plot(data1['steps'], data1['time'], color='red')
plt.plot(data2['steps'], data2['time'], color='green')
plt.savefig('C:/Users/Gondolin/CLionProjects/27/table.png')
plt.show()
