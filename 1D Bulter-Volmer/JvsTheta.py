
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
data = np.loadtxt("J and Theta.txt")
Theta = data[:,0]
J = data[:,1]

#plot figure
plt.figure(figsize = (12,8))
plt.plot(Theta, J, '-r', label = "Cyclic Voltammetry")
plt.title('J Vs Theta (Dimensionless)')
plt.xlabel('Theta')
plt.ylabel('J')
plt.legend(loc = 1)

#plt.savefig('JvsTheta.pdf')
#plt.savefig('JvsTheta.jpg')
plt.show()







