
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
db = 1.6

#calculate I,E,Ip values
I = 2.0*pi*F*D_A*c_A*re*J
E = (Theta * R * T )/ F
Ip = 4*F*re*c_A*D_A*db

#calculate the peak to peak value
max_Iindex = I.argmax()
min_Iindex = I.argmin()
delta_E = E[max_Iindex]-E[min_Iindex]
Jhalf = (min(J)+max(J))*0.5
print Jhalf
print E[2008]

#plot figure
plt.figure(figsize = (12,8))
plt.plot(E, 1e7*I, '-r', label = "Cyclic Voltammetry")
plt.plot([min(E),max(E)],[1e7*Ip,1e7*Ip], '--b', label = "Expected I-lim")
plt.plot([0,0],[-4,0.5], '--g',label = "Expected E(1/2)")
plt.title('I vs E (sigma = 0.001)')
plt.text(0.05, 1e7*min(I)+.05, 'Expected I limit = %.3e' %(Ip))
plt.xlim(min(E),max(E))
plt.ylim(-1,6)
plt.xlabel('E (V)')
plt.ylabel('I (A*1e-7)')
plt.legend(loc = 0)
#plt.savefig('IvsE.pdf')
plt.savefig('IvsE (Ilim).jpg')
plt.show()









