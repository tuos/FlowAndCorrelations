import healpy as hp
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

# Set the number of sources and the coordinates for the input
nsources2 = int(2664001)
nsources = int(3148)
nside = 128
npix = hp.nside2npix(nside)

# Coordinates and the density field f
#thetas = np.random.random(nsources) * np.pi
#phis = np.random.random(nsources) * np.pi * 2.

fs = np.random.randn(nsources)
fs2 = np.random.randn(nsources)

with open("eventFile3.txt") as inputFile2:
    lines2 = inputFile2.readlines()

with open("singleEvent.txt") as inputFile:
    lines = inputFile.readlines()
    #print (lines[1].split()[1])
thetas2 = []
phis2 = []
thetas=[]
phis=[]

for i in range(nsources2):
    thetas2.append(float(lines2[i+1].split()[1]))
    phis2.append(float(lines2[i+1].split()[2]))

for i in range(nsources):    
    thetas.append(float(lines[i+1].split()[1]))
    phis.append(float(lines[i+1].split()[2]))
    #if(thetas[0]<0 or thetas[0]>3.14): 
    #    print("theta out of range")
#print(thetas)

# Go from HEALPix coordinates to indices
indices2 = hp.ang2pix(nside,thetas2, phis2)
indices = hp.ang2pix(nside, thetas, phis)

# Initate the map and fill it with the values
hpxmap = np.zeros(npix, dtype=np.float)
for i in range(nsources):
    #hpxmap[indices[i]] += fs[i]
    hpxmap[indices[i]] += npix*(1.0/nsources)

hpxmap2 = np.zeros(npix, dtype=np.float)
for i in range(nsources):
    hpxmap2[indices2[i]] += npix*(1.0/nsources2)

hpxmapFinal = np.zeros(npix, dtype = np.float)
for i in range(nsources):
    hpxmapFinal[indices[i]] += hpxmap[indices[i]]/hpxmap2[indices[i]]
DPI = 100
SIZE = 400

# Inspect the map
#plt.figure(1)

#map_ring = hp.pixelfunc.reorder(hpxmap, inp = 'NEST', out = 'RING')
#hp.mollview(hpxmap, xsize = SIZE)

hp_smoothed = hp.sphtfunc.smoothing(hpxmapFinal, fwhm=np.radians(5.), iter = 1)

hp.mollview(hp_smoothed, cmap = cm.jet, norm = "hist", xsize = SIZE, title='Real Data smoothed')
plt.savefig("singleNormed.png", dpi = DPI)
hp.graticule()
'''
cl = hp.anafast(hpxmap,lmax=23)
plt.yscale('log')
axes = plt.gca()
axes.set_ylim([0.001,100])
plt.plot(cl)
plt.savefig('powerspect.png')
print(cl)
'''


'''
#plt.figure(2)
# Get the power spectrum
Cl = hp.anafast(hpxmap)
#print(Cl)
plt.plot(Cl)
plt.ylabel('C_{l}')
plt.savefig('plot_toyModel_power_spectrum.png')
'''

