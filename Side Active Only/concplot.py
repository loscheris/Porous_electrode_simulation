
# Import math and plot functions
# -----------------------------------------------------------
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.ticker as mtick
#from matplotlib.ticker import MultipleLocator, FormatStrFormatter
from operator import itemgetter
print "NumPy version = " + np.version.version
print "SciPy version = " + sp.version.version
print "MatPlotLib version = " + mpl.__version__

# Plot parameters
# -----------------------------------------------------------

NoColors = 200
SingleFrame = 10
PrintAll = 1
Cmax = 2
Cmin = 0
cmap = plt.cm.jet

# Global plot parameters
# -----------------------------------------------------------
plt.rcParams['font.size'] = 25
plt.rcParams['axes.linewidth'] = 1.5 
plt.rcParams['lines.linewidth'] = 3
plt.rcParams['lines.markersize'] = 8
plt.rcParams['xtick.major.size'] = 5
plt.rcParams['ytick.major.size'] = 5
plt.rcParams['legend.fancybox'] = False
plt.rcParams['legend.shadow'] = False

# Load data
#------------------------------------------------------------
R = np.loadtxt('data_GridR.txt')
Z = np.loadtxt('data_GridZ.txt')
Ca = np.loadtxt('CONCA.txt')
Cb = np.loadtxt('CONCB.txt')
parameter =  np.genfromtxt('Parameter.txt',usecols=(1,))
sigma = parameter[2]
height = parameter[4]


print "Number of frames = " + str(Ca.shape[0] / Z.size)

#set x,y tick range+spacing
major_x_tick = np.arange(0.995, 1.00501, 0.002)
minor_x_tick = np.arange(0.995, 1.005, 0.001)
major_y_tick = np.arange(height-0.005, height+0.00501, 0.002)
minor_y_tick = np.arange(height-0.005, height+0.005, 0.001)



for frame in range(1,Ca.shape[0] / Z.size+1):
	if PrintAll == 0:
		frame = SingleFrame

	# Generate array for plot
	#------------------------------------------------------------
	CGridA = Ca[ (frame-1)*(Z.size):frame*Z.size, :]
	CGridB = Cb[ (frame-1)*(Z.size):frame*Z.size, :]

	# Plot A
	#------------------------------------------------------------
	plt.figure(figsize = (12,8))
	plt.contourf( R, Z, CGridA, NoColors, cmap=cmap)

	plt.xlim((0.995, 1.005))
	plt.ylim((height-0.005, height+0.005))

	#y-ticks(label format, major+minor tickss)
	#--------------------------------------------------------------
	plt.gca().yaxis.set_major_formatter(mtick.FormatStrFormatter('%.3f'))
	plt.gca().set_yticks(major_y_tick)
	plt.gca().set_yticks(minor_y_tick, minor=True)
	plt.gca().tick_params(axis='y', which = 'major', length=7, color='k', width=1.3, pad=10)	
	plt.gca().tick_params(axis='y', which = 'minor', length=5,color='k')
	
	#x-ticks(label format, major+minor ticks)
	#-------------------------------------------------------------------
	plt.gca().xaxis.set_major_formatter(mtick.FormatStrFormatter('%.3f'))
	plt.gca().set_xticks(major_x_tick)
	plt.gca().set_xticks(minor_x_tick, minor=True)
	plt.gca().tick_params(axis='x', which = 'major', length=7, color='k', width=1.3, pad=10)	
	plt.gca().tick_params(axis='x', which = 'minor', length=5, color='k')

	plt.colorbar(format = '%.1f')

	plt.xlabel('R')
	plt.ylabel('Z')
	plt.title('Concentration of A')
	plt.tight_layout()
	plt.savefig('ConcentrationPlots/CONCA' + str(frame) + '.png')
	plt.show()

	# Plot B
	#------------------------------------------------------------
	plt.figure(figsize = (12,8))
	plt.contourf( R, Z, CGridB, NoColors, cmap=cmap)

	plt.xlim((0.995, 1.005))
	plt.ylim((height-0.005, height+0.005))

	#y-ticks(label format, major+minor tickss)
	#--------------------------------------------------------------
	plt.gca().yaxis.set_major_formatter(mtick.FormatStrFormatter('%.3f'))
	plt.gca().set_yticks(major_y_tick)
	plt.gca().set_yticks(minor_y_tick, minor=True)
	plt.gca().tick_params(axis='y', which = 'major', length=7, color='k', width=1.3, pad=10)	
	plt.gca().tick_params(axis='y', which = 'minor', length=5,color='k')
	
	#x-ticks(label format, major+minor ticks)
	#-------------------------------------------------------------------
	plt.gca().xaxis.set_major_formatter(mtick.FormatStrFormatter('%.3f'))
	plt.gca().set_xticks(major_x_tick)
	plt.gca().set_xticks(minor_x_tick, minor=True)
	plt.gca().tick_params(axis='x', which = 'major', length=7, color='k', width=1.3, pad=10)	
	plt.gca().tick_params(axis='x', which = 'minor', length=5, color='k')

	plt.colorbar(format = '%.1f')
	
	plt.xlabel('R')
	plt.ylabel('Z')
	plt.title('Concentration of B')
	plt.tight_layout()
	plt.savefig('ConcentrationPlots/CONCB' + str(frame) + '.png')

	if PrintAll == 0:
		plt.show()
		break







