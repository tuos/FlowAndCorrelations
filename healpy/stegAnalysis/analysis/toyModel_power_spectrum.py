import healpy as hp
import numpy as np
import matplotlib.pyplot as plt

# Set the number of sources and the coordinates for the input
nsources = int(2000)
nside = 8
npix = hp.nside2npix(nside)

# Coordinates and the density field f
#thetas = np.random.random(nsources) * np.pi
#phis = np.random.random(nsources) * np.pi * 2.

fs = np.random.randn(nsources)

with open("eventFile.txt") as inputFile:
    lines = inputFile.readlines()
    #print (lines[1].split()[1])
thetas=[]
phis=[]
for i in range(nsources):    
    thetas.append(float(lines[i+1].split()[1]))
    phis.append(float(lines[i+1].split()[2]))
    #if(thetas[0]<0 or thetas[0]>3.14): 
    #    print("theta out of range")
#print(thetas)

# Go from HEALPix coordinates to indices
indices = hp.ang2pix(nside, thetas, phis)

# Initate the map and fill it with the values
hpxmap = np.zeros(npix, dtype=np.float)
for i in range(nsources):
    #hpxmap[indices[i]] += fs[i]
    hpxmap[indices[i]] += 1.0

DPI = 100
SIZE = 400

# Inspect the map
#plt.figure(1)

#hp.mollview(hpxmap, xsize = SIZE)
hp_smoothed = hp.smoothing(hpxmap, fwhm=np.radians(15.))
hp.mollview(hp_smoothed, xsize = SIZE, title='Toy model smoothed')
plt.savefig("plot_toyModel_2000m_smoothed.png", dpi = DPI)


'''
#plt.figure(2)
# Get the power spectrum
Cl = hp.anafast(hpxmap)
#print(Cl)
plt.plot(Cl)
plt.ylabel('C_{l}')
plt.savefig('plot_toyModel_power_spectrum.png')
'''

