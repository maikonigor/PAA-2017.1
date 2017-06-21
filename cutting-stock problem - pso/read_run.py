import numpy as np
import matplotlib.pyplot as plt

file = "RUN.txt"

data = np.loadtxt(file)

x = data[:200,0]
y = data[:200,1]

plt.plot(x,y,linewidth=0.5)
# plt.axis([x.min(), x.max(),y.min(), y.max()])
plt.show()
