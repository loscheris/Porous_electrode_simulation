
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

sigma = 1e6
data1 = np.loadtxt("J1.txt")
data2 = np.loadtxt("J2.txt")
Theta = data1[:,0]
J1 = data1[:,1]
J2 = data2[:,1]
J = J1+J2


#constants
R = 8.31
T = 298.0
pi = np.pi
F = 96485.0
D_A = 1.83e-9
c = 1000.0
re =  1e-7
db = 1.0
height = 1.0
width = 1.0
alpha = 0.5


#calculate I,E,Ip values
I = 2.0*pi*F*D_A*c*J*re
E = (Theta * R * T )/ F
v = (sigma*R*T*D_A)/(F * re**2.0)

#2D expection
#if Jvalue == 1:
#    Ip = -4.0*F*re*c*db*D_A*(0.34* np.exp(-.66*np.sqrt(sigma/db))+0.66-0.13*np.exp(-11.0/np.sqrt(sigma/db))+0.351*np.sqrt(sigma/db))
#else:
#   Ip = -4.0*F*re*c*db*D_A*(0.34* np.exp(-.66*np.sqrt(sigma/db))+0.66-0.13*np.exp(-11.0/np.sqrt(sigma/db))+0.351*np.sqrt(sigma/db))*2*height/width

#Randles Sevcik Revesible
Ip2 = -0.446 * F * c* pi* re**2 * np.sqrt((db*F*D_A*v)/(R*T))*2*height/width
Ip1 = -0.446 * F * c* pi* re**2 * np.sqrt((db*F*D_A*v)/(R*T))
Ip = Ip1 + Ip2

#Randles Sevcik Irreversible
#if Jvalue == 1:
#   Ip = -0.496 * F * c* pi* re**2 * np.sqrt((db*F*D_A*v)/(R*T))*np.sqrt(alpha)
#else:
#    Ip = -0.496 * F * c* pi* re**2 * np.sqrt((db*F*D_A*v)/(R*T))*np.sqrt(alpha)*2*height/width

#calculate the peak to peak value
max_Iindex = I.argmax()
min_Iindex = I.argmin()
delta_E = E[max_Iindex]-E[min_Iindex]
print 'max index: %s'%max_Iindex
print 'min index: %s'%min_Iindex


#plot figure
rescale = 1e7
plt.figure(figsize = (12,8))
plt.plot(E, rescale*I, '-r', label = "Cyclic Voltammetry")
#plt.plot([min(E),max(E)],[rescale*Ip,rescale*Ip], '--b', label = "Expected Ip")


#plt.text(0.0, rescale*min(I)+0.6, 'Expected Ip = %.3e' %(Ip))
plt.text(-0.1, rescale*max(I),b'Peak to peak difference: %.3fV\nPeak J(dimensionless): %.3e' %(delta_E,min(J)))


plt.xlim(min(E),max(E))
#plt.ylim(-6,6)

rescale2 = 1/rescale
plt.xlabel('E (V)')
plt.ylabel('I (*%0.0e A)' %rescale2)

#plt.legend(loc = 1)
plt.title('I vs E ')


plt.savefig('J2.jpg')
plt.show()








