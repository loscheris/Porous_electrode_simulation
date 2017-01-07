
# Import math and plot functions
# -----------------------------------------------------------
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib as mpl
mpl.rc ('font', family='Times New Roman')

# Global plot parameters
# -----------------------------------------------------------
plt.rcParams['font.size'] = 30
plt.rcParams['axes.linewidth'] = 1.5
plt.rcParams['lines.linewidth'] = 3
plt.rcParams['lines.markersize'] = 20
plt.rcParams['xtick.major.size'] = 5
plt.rcParams['ytick.major.size'] = 5
plt.rcParams['legend.fancybox'] = False
plt.rcParams['legend.shadow'] = False
plt.rcParams['legend.fontsize'] = 25

#load data
data1 = np.loadtxt("reversible.txt")
data2 = np.loadtxt("quasi-reversible.txt")
data3 = np.loadtxt("irreversible.txt")
Theta = data1[:,0]
J1 = data1[:,1]
J2 = data2[:,1]
J3 = data3[:,1]


#constants
R = 8.31
T = 298.0
pi = np.pi
F = 96485.0
D_A = 1e-9
c_A = 1000
e =  1e-3
sigma = 100.0
db = 1
alpha = 0.5

#calculate I,E,Ip values
I1 = J1 * (pi * e * F * D_A * c_A)
I2 = J2 * (pi * e * F * D_A * c_A)
I3 = J3 * (pi * e * F * D_A * c_A)
E = (Theta * R * T )/ F
v = (sigma*R*T*D_A)/(F * e**2.0)


#plot figure
plt.figure(figsize = (12,8))
plt.plot(E, 1e4*I3, '--g', label = "Irreversible")
plt.plot(E, 1e4*I2, '--b', label = "Quasi-reversible")
plt.plot(E, 1e4*I1, '-r', label = "Reversible")
plt.xlim(min(E),max(E))
plt.ylim(-15,13)
plt.xlabel(r'$E\ (V)$')
plt.ylabel(r'$I\ (\times\mathregular{10^{-4}}\ A)$')
plt.legend(loc = 4)
plt.savefig('IvsE.pdf')
plt.tight_layout
#plt.savefig('IvsE.jpg')
plt.show()
