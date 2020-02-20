import healpy as hp
import numpy as np
import matplotlib.pyplot as plt

# Set the number of sources and the coordinates for the input
nsources = int(3000)
nside = 8
npix = hp.nside2npix(nside)

# Coordinates and the density field f
thetas = np.random.random(nsources) * np.pi
phis = np.random.random(nsources) * np.pi * 2.
fs = np.random.randn(nsources)

# Go from HEALPix coordinates to indices
indices = hp.ang2pix(nside, thetas, phis)

# Initate the map and fill it with the values
hpxmap = np.zeros(npix, dtype=np.float)
for i in range(nsources):
    hpxmap[indices[i]] += fs[i]
DPI = 100
SIZE = 400

# Inspect the map
#plt.figure(1)
#hp.mollview(hpxmap, xsize = SIZE)
hp_smoothed = hp.smoothing(hpxmap, fwhm=np.radians(20.))
hp.mollview(hp_smoothed, xsize = SIZE, title='Map smoothed')

plt.savefig("noise_data_smooth.png", dpi = DPI)

'''
#plt.figure(2)
# Get the power spectrum
Cl = hp.anafast(hpxmap)
#print(Cl)
plt.plot(Cl)
plt.ylabel('power spectrum')
plt.savefig('power_spectrum.png')
'''

