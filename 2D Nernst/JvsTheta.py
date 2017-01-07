
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

#calculate Jp value from sigma
#sigma = 100.0
#Jp = -.446 * np.sqrt(sigma)

#calculate peak to peak difference
#max_Jindex = J.argmax()
#min_Jindex = J.argmin()
#delta_theta = Theta[max_Jindex]-Theta[min_Jindex]

#plot figure
plt.figure(figsize = (12,8))
plt.plot(Theta, J, '-r', label = "Cyclic Voltammetry")
#plt.plot([-20,20],[Jp,Jp], '--b' , label = "Expected Max Jp")
plt.title('J Vs Theta (Dimensionless)')
#plt.text(-2, Jp-.4, 'Expected Max Jp = %s' %Jp)
#plt.text(-19, 3, b'Peak to peak difference: %s' %delta_theta)
plt.xlabel('Theta')
plt.ylabel('J')
plt.legend(loc = 1)

#plt.savefig('JvsTheta.pdf')
plt.savefig('JvsTheta.jpg')
plt.show()







