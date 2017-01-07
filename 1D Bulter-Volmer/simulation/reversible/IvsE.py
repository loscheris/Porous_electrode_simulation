
# Import math and plot functions
# -----------------------------------------------------------
import numpy as np
import matplotlib.pyplot as plt
import math

# Global plot parameters
# -----------------------------------------------------------
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
I = J * (pi * e * F * D_A * c_A)
E = (Theta * R * T )/ F
v = (sigma*R*T*D_A)/(F * e**2.0)
Ip = -0.446 * F * c_A* pi* e**2 * np.sqrt((db*F*D_A*v)/(R*T))
#Ip = 0.496*np.sqrt(alpha)*pi*e**2 * np.sqrt((db*F*D_A*v)/(R*T))

#calculate the peak to peak value
max_Iindex = I.argmax()
min_Iindex = I.argmin()
delta_E = E[max_Iindex]-E[min_Iindex]

#plot figure
plt.figure(figsize = (12,8))
plt.plot(E, 1e5*I, '-r', label = "Cyclic Voltammetry")
plt.plot([min(E),max(E)],[1e5*Ip,1e5*Ip], '--b', label = "Expected Ip")
plt.title('I vs E (A -> B)')
plt.text(0.0, 1e7*min(I)+0.6, 'Expected Ip = %.3e' %(Ip))
plt.text(-0.5, 12, b'Peak to peak difference: %.3fV' %delta_E)
plt.xlim(min(E),max(E))
plt.xlabel('E (V)')
plt.ylabel('I (A*1e-5)')
plt.legend(loc = 1)
#plt.savefig('IvsE.pdf')
plt.savefig('IvsE.jpg')
plt.show()









