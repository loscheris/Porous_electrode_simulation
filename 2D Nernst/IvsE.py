
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
c_A = 1.0
re =  1e-3
sigma = 10000.0

#calculate I,E,Ip values
I = 2.0*pi*F*D_A*c_A*re*J
E = (Theta * R * T )/ F
v = (sigma*R*T*D_A)/(F * re**2.0)
Ip = -4.0*F*re*c_A*D_A*(0.34* math.exp(-.66*np.sqrt(sigma))+0.66-0.13*math.exp(-11.0/np.sqrt(sigma))+0.351*np.sqrt(sigma))

#calculate the peak to peak value
max_Iindex = I.argmax()
min_Iindex = I.argmin()
delta_E = E[max_Iindex]-E[min_Iindex]

#plot figure
rescale = 1e6
plt.figure(figsize = (12,8))
plt.plot(E, rescale*I, '-r', label = "Cyclic Voltammetry")
plt.plot([min(E),max(E)],[rescale*Ip,rescale*Ip], '--b', label = "Expected Ip")


plt.text(0.0, rescale*min(I)+0.6, 'Expected Ip = %.3e' %(Ip))
plt.text(-0.5, 12, b'Peak to peak difference: %.3fV' %delta_E)

plt.xlim(min(E),max(E))
#plt.ylim(-20,15)

rescale2 = 1/rescale
plt.xlabel('E (V)')
plt.ylabel('I (*%0.0e A)' %rescale2)

plt.legend(loc = 1)
plt.title('I vs E')

plt.savefig('IvsE.jpg')
plt.show()









