
# Import math and plot functions
# -----------------------------------------------------------
import numpy as np
import matplotlib.pyplot as plt
import math

plt.rcParams['font.size'] = 20
plt.rcParams['axes.linewidth'] = 1.5 
plt.rcParams['lines.linewidth'] = 3
plt.rcParams['lines.markersize'] = 20
plt.rcParams['xtick.major.size'] = 5
plt.rcParams['ytick.major.size'] = 5
plt.rcParams['legend.fancybox'] = False
plt.rcParams['legend.shadow'] = False
plt.rcParams['legend.fontsize'] = 20

#load data
data = np.loadtxt("Grid And Conc.txt")
x = data[:,0]
conc = data[:,1]

x_prime = x

#plot figure
plt.figure(figsize = (12,8))
plt.plot(x_prime, conc, '-r')
plt.title("Concentration vs X at medium T")



plt.xlabel('x')
plt.ylabel('conc')
plt.legend(loc = 1)

plt.savefig('conc vs x.pdf')
plt.savefig('conc vs x.jpg')
plt.show()

