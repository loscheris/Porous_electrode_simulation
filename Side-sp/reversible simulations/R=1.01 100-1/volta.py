
# Import math and plot functions
# -----------------------------------------------------------
import numpy as np
import matplotlib.pyplot as plt
import math
#from matplotlib.legend_handler import HandlerLine2D

# Global plot parameters
# -----------------------------------------------------------
plt.rcParams['font.size'] = 20
plt.rcParams['axes.linewidth'] = 1.5 
plt.rcParams['lines.linewidth'] = 2.5
plt.rcParams['lines.markersize'] = 20
plt.rcParams['xtick.major.size'] = 5
plt.rcParams['ytick.major.size'] = 5
plt.rcParams['legend.fancybox'] = False
plt.rcParams['legend.shadow'] = False
plt.rcParams['legend.fontsize'] = 20

#constants
#------------------------------------------------------
R = 8.31
T = 298.0
pi = np.pi
F = 96485.0
D_A = 1.183e-9
c = 1000.0
re = 1e-7
db = 1.0
height = 10.0
width = 1.0
alpha = 0.5
k0= 1e-2
sigma = 1e-4
rescale = 1e10
rescale2 = 1/rescale
Ip_linear = 1.147e-10 * rescale
Epp_linear = 0.056
timestep_per_stair = 320
total_timestep = 320000
no_record_per_cycle = total_timestep/timestep_per_stair

#load data
#----------------------------------------------------
#data1 = np.loadtxt("J1.txt")
data3 = np.loadtxt("J3.txt")
data2 = np.loadtxt("J2.txt")
time = data2[:,0]
#J1 = data1[:,1]
J2 = data2[:,1]
Theta = data2[:,2]
J = J2
Time= (time*re**2)/D_A
I = 2.0*pi*F*D_A*c*J*re
E = Theta*T*R/F
time_per_potential_step=(time[1]*timestep_per_stair*re**2)/D_A

E_1= data3[:,0]
J_1= data3[:,1]
I_lin = 2.0*pi*F*D_A*c*J_1*re
E_lin = E_1*T*R/F

#create variables
#--------------------------------------------------------
p = [0.0]*no_record_per_cycle
E_=[0.0]*no_record_per_cycle
#every time
Ip= [0.0]*timestep_per_stair
delta_E=[0.0]*timestep_per_stair
recordtime = [0]*timestep_per_stair
#odd time
Ip_odd=[0.0]*(timestep_per_stair/2)
delta_Eodd = [0.0]*(timestep_per_stair/2)
recordtime_odd = [0.0]*(timestep_per_stair/2)
#even time
Ip_even=[0.0]*(timestep_per_stair/2)
delta_Eeven = [0.0]*(timestep_per_stair/2)
recordtime_even=[0.0]*(timestep_per_stair/2)
#average time
Ip_avg=[0.0]*(timestep_per_stair/2)
delta_Eavg = [0.0]*(timestep_per_stair/2)
recordtime_avg=[0.0]*(timestep_per_stair/2)

alpha=[0.20,0.40,0.60,0.80,1]
a=0
#calculations of average line
#------------------------------------------------------------------------
k=[224,288,352,416,478]
#k=[225,289,353,417,479]
fig, ax1 = plt.subplots(figsize=(12, 8))
for m in k:
	
	for n in range (no_record_per_cycle):
		if n*timestep_per_stair+m < total_timestep:
			p[n] = (I[n*timestep_per_stair+m]+I[n*timestep_per_stair+m+1])*rescale/2
			E_[n] = E[n*timestep_per_stair+m]	
	ax1.plot(E_,p,'-',label="alpha=%s" %alpha[a])
	a=a+1

ax1.plot(E_lin, I_lin*rescale, '-k',label="linear")

ax1.set_xlim(min(E_),max(E_))
ax1.set_xlabel("E")
ax1.set_ylabel('I (*%0.0e A)' %rescale2)
ax1.legend(loc=4)





#ax1.set_ylim(-8,1)
#ax1.set_xlabel('Record time (%)')
#ax1.set_ylabel('Ip (*%0.0e A)' %rescale2)



#save and show
#------------------------------------------------------------------
plt.savefig('PLOT.jpg')

plt.show()

