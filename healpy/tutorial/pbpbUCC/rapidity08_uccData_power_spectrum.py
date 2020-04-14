import healpy as hp
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.colors import LogNorm

# Set the number of sources and the coordinates for the input
#nsources = int(2664001)
#nsources = int(3149)
nsources = int(1268174)

nside = 64
npix = hp.nside2npix(nside)

# npix= 12*nside^2
# Coordinates and the density field f
#thetas = np.random.random(nsources) * np.pi
#phis = np.random.random(nsources) * np.pi * 2.

fs = np.random.randn(nsources)

with open("./eventFile_data_noHead_eta08.txt") as inputFile:
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
    #hpxmap[indices[i]] += 1.0
    hpxmap[indices[i]] += 12.0*nside*nside/nsources
#for j in range(npix):
#    if hpxmap[j] < 0.000001:
#        hpxmap[j] = 0.000001

DPI = 100
SIZE = 800

# Inspect the map
#plt.figure(1)

#hp.mollview(hpxmap, xsize = SIZE)
#map_ring = hp.pixelfunc.reorder(hpxmap, inp='NEST', out='RING')
hp_smoothed = hp.sphtfunc.smoothing(hpxmap, fwhm=np.radians(5))
#hp_smoothed = hp.sphtfunc.smoothing(hpxmap, fwhm=np.radians(5.0*3.14/180))
#hp_smoothed = hp.smoothing(hpxmap, fwhm=np.radians(5.0*3.14/180))
#hp_smoothed = hp.sphtfunc.smoothing(hpxmap, sigma=np.radians(5.0*3.14/180))
#hp_smoothed = hp.smoothing(hpxmap, fwhm=60, arcmin=True)
#hp.mollview(hp_smoothed, nest=False, xsize = SIZE, cmap=cm.jet, norm = 'hist', title='CMS UCC smoothed')
#cmap_tmp = cm.jet
#cmap_tmp.set_bad("gray")
#cmap_tmp.set_under("white")
hp.mollview(hp_smoothed, nest=False, xsize = SIZE, cmap=cm.jet, norm="hist", title='CMS UCC smoothed') #jet/rainbow/seismic/bwr; norm="hist"/LogNorm()
hp.graticule()
#plt.savefig("plot_uccData_3149m_smoothed.png", dpi = DPI)
#plt.savefig("plot_rapidity08_uccData_allEvents_smoothed.png", dpi = DPI)
plt.savefig("plot_rapidity08_uccData_allEvents_withnormhist_smoothed.png", dpi = DPI)
#plt.savefig("plot_uccData_oneEvents_smoothed.png", dpi = DPI)


'''
#plt.figure(2)
# Get the power spectrum
Cl = hp.anafast(hpxmap)
#print(Cl)
plt.plot(Cl)
plt.ylabel('C_{l}')
plt.savefig('plot_uccData_power_spectrum.png')
'''

