
import healpy as hp
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import scipy.special as spc
import math
import matplotlib as mpl
from scipy.special import lpmn
import scipy.integrate as integrate
from scipy.integrate import quad
from numpy import sin, cos
from matplotlib.cm import ScalarMappable
import random
# Set the number of sources and the coordinates for the input


nsources = int(199999)
nside = 8
npix = hp.nside2npix(nside)
SIZE = 400
DPI = 100
# Coordinates and the density field f
#thetas = np.random.random(nsources) * np.pi
#phis = np.random.random(nsources) * np.pi * 2.

#fs = np.random.randn(nsources)

'''
with open("eventFileFullTot_iso.txt") as inputFile2:
   lines2 = inputFile2.readlines()

thetas2 = []
phis2 = []

for i in range(nsources):
   thetas2.append(float(lines2[i+1].split()[1]))
   phis2.append(float(lines2[i+1].split()[2]))

indices2 = hp.ang2pix(nside, thetas2, phis2)
'''

cl = []
for l in range(24):
   cl.append(0)
indices2 = []
hpxmap2 = np.zeros(npix, dtype = np.float)
events = 5000
mult = 2500
arr = [[0]*(mult)]*events
for i in range(events):
    #print(i)
    hpxmap2 = np.zeros(npix, dtype = np.float)
    for k in range(mult):
       ipix = random.randint(0, npix-1)
       #hpxmap2[indices2[i]] += 1.0
       hpxmap2[ipix] += 1
       #indices2.append(ipix)
       arr[i][k] = hp.pix2ang(nside,ipix)
       #hpxmap[ipix] += 1
       #print(hp.pix2ang(nside,ipix))

    if i%100 == 0:
        print("First loop with i = "+str(i))

'''
    c = hp.anafast(hpxmap)
    for x in range(len(c)):
       cl[x] = cl[x] + c[x]
for y in range(len(cl)):
    cl[y] = cl[y] /(1.0*events)
       
'''
hpxmapFinal = np.zeros(npix, dtype = np.float)
for i in range(events): 
    if i%100 == 0:
        print("Second loop with i = "+str(i))
    c = np.zeros(24)   
    hpxmapFinal = np.zeros(npix, dtype = np.float)
    hpxmap = np.zeros(npix, dtype = np.float)
    for k in range(mult):
       indices = hp.ang2pix(nside,arr[i][k][0],arr[i][k][1])
       indices2.append(indices)
       hpxmap[indices] += 1
    for l in range(mult):
       hpxmapFinal[indices2[l]] += (hpxmap[indices2[l]]/hpxmap2[indices2[l]]) * (npix* (1.0/mult))

    c = hp.anafast(hpxmapFinal)
    #print(c)
    for x in range(len(c)):
       cl[x] = cl[x] + c[x]
for y in range(len(cl)):
    cl[y] = cl[y] /(1.0*events)

print(cl)


plt.yscale('log')
plt.plot(cl)
plt.savefig("powerspect_iso2.png")
#hpxmap2[1] = 50
#hpxmap2[npix-2] = 150

#hp_smoothed = hp.sphtfunc.smoothing(hpxmap2, fwhm=np.radians(1), iter = 1)
'''
hp.mollview(hpxmap2, cmap = cm.jet, xsize = SIZE, min = events*mult/npix*0.9, max = events*mult/npix*1.1, title='Isotropic randomised')
#fig = plt.gcf()
#ax = plt.gca()
#norm = mpl.colors.Normalize(vmin = 50, vmax = 150)
#image = ax.get_images()[0]
#cmap = fig.colorbar(image, norm = norm, orientation = 'horizontal')

hp.graticule()
plt.savefig("map_iso.png", dpi = DPI)

'''
'''
cl = []
for l in range(24):
   cl.append(0)

i = 0
events = 100
for x in range(events):
 
    i += 1
    j = x+1
    phis = []
    thetas = []
      #print(lines[i+1].split()[0])
      thetas.append(float(lines[i].split()[1]))
      phis.append(float(lines[i].split()[2]))
      i+=1

    indices = hp.ang2pix(nside, thetas, phis)
    hpxmap = np.zeros(npix, dtype = np.float)
    
    for k in range(len(thetas)):
      hpxmap[indices[k]] += 1.0

'''

