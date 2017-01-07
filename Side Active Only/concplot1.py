
# Import math and plot functions
# -----------------------------------------------------------
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import matplotlib as mpl
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
#theta = np.loadtxt('data_ConcentrationsTheta.txt')

print "Number of frames = " + str(Ca.shape[0] / Z.size)

xmin = min(R)
xmax = max(R)
ymin = min(Z)
ymax = max(Z)

for frame in range(1, Ca.shape[0] / Z.size + 1):
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

	plt.xlim((xmin, xmax))
	plt.ylim((ymin, ymax))

	#plt.clim((0, 2))

	plt.gca().get_xaxis().get_major_formatter().set_powerlimits((-3, 4))
	plt.gca().get_yaxis().get_major_formatter().set_powerlimits((-3, 4))

	plt.colorbar(format = '%.1f')

	plt.xlabel('R')
	plt.ylabel('Z')
	plt.title('Concentration of A')

	plt.savefig('ConcentrationPlots/CONCA' + str(frame) + '.png')
	
	#plt.savefig('ConcentrationPlots/plot_ConcentrationA_' + str(frame) + '.eps')
	#plt.savefig('ConcentrationPlots/plot_ConcentrationA_' + str(frame) + '.pdf')

	# Plot B
	#------------------------------------------------------------
	plt.figure(figsize = (12,8))
	plt.contourf( R, Z, CGridB, NoColors, cmap=cmap)

	plt.xlim((xmin, xmax))
	plt.ylim((ymin, ymax))

	#plt.clim((0, 2))

	plt.gca().get_xaxis().get_major_formatter().set_powerlimits((-3, 4))
	plt.gca().get_yaxis().get_major_formatter().set_powerlimits((-3, 4))

	plt.colorbar(format = '%.1f')

	plt.xlabel('R')
	plt.ylabel('Z')
	plt.title('Concentration of B')

	plt.savefig('ConcentrationPlots/CONCB' + str(frame) + '.png')
	plt.show()
	#plt.savefig('ConcentrationPlots/plot_ConcentrationB_' + str(frame) + '.eps')
	#plt.savefig('ConcentrationPlots/plot_ConcentrationB_' + str(frame) + '.pdf')

	
	if PrintAll == 0:
		plt.show()
		break







