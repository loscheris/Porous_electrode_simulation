
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



#constants
R = 8.31
T = 298.0
pi = np.pi
F = 96485.0
D_A = 1.83e-9
c = 1000.0
re =  1e-7
db = 1.0
height = 10.0
width = 1.0
alpha = 0.5
k0= 1e-4

#load data

sigma = 1e7

data1 = np.loadtxt("J1.txt")
data2 = np.loadtxt("J2.txt")
t=data1[:,0]
J1 = data1[:,1]
J2 = data2[:,1]
J = J1 + J2
T= (t*re**2)/D_A


#calculate I,E,Ip values
I = 2.0*pi*F*D_A*c*J*re



#plot figure
rescale = 1e10
plt.figure(figsize = (12,8))
plt.plot(T, rescale*I, '-r', label = "Cyclic Voltammetry")



plt.xlim(min(T),max(T))


rescale2 = 1/rescale
plt.xlabel('T (s)')
plt.ylabel('I (*%0.0e A)' %rescale2)

#plt.legend(loc = 1)
plt.title('I vs T ')


plt.savefig('J2-t.jpg')
plt.show()








