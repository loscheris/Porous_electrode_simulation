
# Import math and plot functions
# -----------------------------------------------------------
import numpy as np
import matplotlib.pyplot as plt

# Global plot parameters
# -----------------------------------------------------------
plt.rcParams['font.size'] = 24
plt.rcParams['axes.linewidth'] = 1.5 
plt.rcParams['lines.linewidth'] = 3
plt.rcParams['lines.markersize'] = 20
plt.rcParams['xtick.major.size'] = 5
plt.rcParams['ytick.major.size'] = 5
plt.rcParams['legend.fancybox'] = False
plt.rcParams['legend.shadow'] = False
plt.rcParams['legend.fontsize'] = 20

data = np.loadtxt("Grid And Conc.txt")
grid = data[:,0]
conc = data[:,1]


plt.figure(figsize = (12,8))
plt.plot(grid, conc, 'r', label = "data.txt")


plt.xlabel('x')
plt.ylabel('conc')
plt.legend(loc = 1)

plt.savefig('ConcVsX.pdf')
plt.show()


