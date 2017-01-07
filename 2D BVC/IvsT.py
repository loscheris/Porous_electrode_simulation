
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
c_A = 1.0
re =  1.0e-3
db= 1.0

t = re*re*T/D_A
I = -2.0*pi*F*D_A*c_A*re*J


X = np.linspace(0.0001, 8.0, 10000, endpoint=True)
Y = F*re*re*c_A*np.sqrt(D_A/(pi*X))

x1 = np.linspace(0.0001, 8.0, 10000, endpoint=True)
y1= x1
y1 = 4.0*F*re*c_A*D_A*db*(0.7854+0.8863/np.sqrt(4.0*db*D_A*x1/(re*re))+0.2146*np.exp(-.7823/np.sqrt(4.0*db*D_A*x1/(re*re))))

#plot figure
plt.figure(figsize = (12,8))
plt.plot(t, 1e5*I, '-r', label = "Simulated Chronoamperogram")
plt.plot(X, 1e5*Y , '--b',label = "Cottrell Equation")
plt.plot(x1, 1e5*y1 ,'--g', label = "Shoup-Szabo")

plt.ylim(0,4)
plt.xlabel('t (s)')
plt.ylabel('I (*1e-5 A)')
plt.legend(loc = 1)
plt.title('I vs t')

#plt.savefig('Ivssqrt(T).pdf')
plt.savefig('IvsT.jpg')
plt.show()

