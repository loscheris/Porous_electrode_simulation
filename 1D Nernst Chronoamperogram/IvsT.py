
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
data = np.loadtxt("J and T.txt")
T = data[:,0]
J = data[:,1]

pi = np.pi
F = 96485.0
D_A = 1.0e-9
c_A = 1.0e-3
e =  1.0e-3


t = e*e*T/D_A


I = J * (pi * e * F * D_A * c_A)
#gradient = (1.0 * F * pi * e**2 * c_A* np.sqrt(D_A))/np.sqrt(pi)

#X = np.linspace(0.0, t[0], 1000, endpoint=True)
#Y = -gradient * X

#plot figure
plt.figure(figsize = (12,8))
plt.plot(t, -1e5*I, '-r', label = "Simulated Chronoamperogram")
#plt.plot(X, 1e5*Y , label = "Cottrell Equation")


plt.xlabel('T (s)')
plt.ylabel('I (A*1e-5)')
#plt.legend(loc = 1)
#plt.title('I vs 1/sqrt(time)')

#plt.savefig('Ivssqrt(T).pdf')
plt.savefig('IvsT.jpg')
plt.show()

