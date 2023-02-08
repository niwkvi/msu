import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np


data1 = pd.read_csv('C:/Users/Gondolin/CLionProjects/27/table1.csv', delimiter=',')
data2 = pd.read_csv('C:/Users/Gondolin/CLionProjects/27/table2.csv', delimiter=',')

x1 = np.array(data1['size'])
y1 = np.array(data1['density'])
z1 = np.array(data1['avgTime'])

x2 = np.array(data2['size'])
y2 = np.array(data2['density'])
z2 = np.array(data2['avgTime'])

fig = plt.figure()
ax = Axes3D(fig)

ax.plot(x1, y1, z1, color='red')
ax.plot(x2, y2, z2, color='green')
plt.show()
