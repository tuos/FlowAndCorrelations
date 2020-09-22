
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
clSqr = []
clErr = []
cl09 = []
clSqr09 = []
clErr09 = []
cl20 = []
clSqr20 = []
clErr20 = []
cl30 = []
clSqr30 = []
clErr30 = []
for l in range(24):
   cl.append(0)
   clSqr.append(0)
   clErr.append(0)
   cl09.append(0)
   clSqr09.append(0)
   clErr09.append(0)
   cl20.append(0)
   clSqr20.append(0)
   clErr20.append(0)
   cl30.append(0)
   clSqr30.append(0)
   clErr30.append(0)


indices2 = []
hpxmap2 = np.zeros(npix, dtype = np.float)
events = 8000
mult = 3000
#arr = [[0]*(mult)]*events
#arr = [ [0]*mult for i in range(events)]
arr = [[0 for i in range(mult)] for j in range(events)] 
for i in range(events):
    if i%50 == 0:
        print("First loop with i = "+str(i)+', and events = '+str(events))
    #print(i)
    #hpxmap2 = np.zeros(npix, dtype = np.float)
    for k in range(mult):
       ipix = random.randint(0, npix-1)
       #if k == 0:
       #print('i = '+str(i)+'   ipix = '+str(ipix))
       #hpxmap2[indices2[i]] += 1.0
       hpxmap2[ipix] += 1
       #indices2.append(ipix)
       arr[i][k] = hp.pix2ang(nside,ipix) # First theat, then phi angles
       #hpxmap[ipix] += 1
       #print('i = '+str(i)+', First loop, angles: '+str(hp.pix2ang(nside,ipix)))
       #print('i = '+str(i)+', First loop, angles: '+str(arr[i][k]))


#hpxmapFinal = np.zeros(npix, dtype = np.float)
for i in range(events): 
    if i%50 == 0:
        print('Second loop with i = '+str(i)+', and events = '+str(events))
    c = np.zeros(24)   
    c09 = np.zeros(24)   
    c20 = np.zeros(24)   
    c30 = np.zeros(24)   
    hpxmapFinal = np.zeros(npix, dtype = np.float)
    hpxmap = np.zeros(npix, dtype = np.float)
    hpxmapFinalEta09 = np.zeros(npix, dtype = np.float)
    hpxmapEta09 = np.zeros(npix, dtype = np.float)
    hpxmapFinalEta20 = np.zeros(npix, dtype = np.float)
    hpxmapEta20 = np.zeros(npix, dtype = np.float)
    hpxmapFinalEta30 = np.zeros(npix, dtype = np.float)
    hpxmapEta30 = np.zeros(npix, dtype = np.float)
    for k in range(mult):
       #print('arr[i][k] = '+str(arr[i][k]))
       indices = hp.ang2pix(nside,arr[i][k][0],arr[i][k][1])
       #print('i = '+str(i)+', indices = '+str(indices))
       #indices2.append(indices)
       hpxmap[indices] += 1
       if(abs(-math.log(math.tan(arr[i][k][0]/2)))<0.9):
           hpxmapEta09[indices] += 1
       if(abs(-math.log(math.tan(arr[i][k][0]/2)))<2.0):
           hpxmapEta20[indices] += 1
       if(abs(-math.log(math.tan(arr[i][k][0]/2)))<3.0):
           hpxmapEta30[indices] += 1

    for n in range(npix):
       if (hpxmap2[n] > 0):
          hpxmapFinal[n] = (hpxmap[n]/hpxmap2[n]) * (events)
          hpxmapFinalEta09[n] = (hpxmapEta09[n]/hpxmap2[n]) * (events)
          hpxmapFinalEta20[n] = (hpxmapEta20[n]/hpxmap2[n]) * (events)
          hpxmapFinalEta30[n] = (hpxmapEta30[n]/hpxmap2[n]) * (events)

    c = hp.anafast(hpxmapFinal)
    c09 = hp.anafast(hpxmapFinalEta09)
    c20 = hp.anafast(hpxmapFinalEta20)
    c30 = hp.anafast(hpxmapFinalEta30)
    #print(c)
    for x in range(len(c)):
       cl[x] = cl[x] + c[x]
       clSqr[x] = clSqr[x] + c[x]*c[x]
       cl09[x] = cl09[x] + c09[x]
       clSqr09[x] = clSqr09[x] + c09[x]*c09[x]
       cl20[x] = cl20[x] + c20[x]
       clSqr20[x] = clSqr20[x] + c20[x]*c20[x]
       cl30[x] = cl30[x] + c30[x]
       clSqr30[x] = clSqr30[x] + c30[x]*c30[x]

for y in range(len(cl)):
    cl[y] = cl[y] /(1.0*events)
    clSqr[y] = clSqr[y] /(1.0*events)
    clErr[y] = math.sqrt((clSqr[y] - cl[y]*cl[y])/(1.0*events))
    cl09[y] = cl09[y] /(1.0*events)
    clSqr09[y] = clSqr09[y] /(1.0*events)
    clErr09[y] = math.sqrt((clSqr09[y] - cl09[y]*cl09[y])/(1.0*events))
    cl20[y] = cl20[y] /(1.0*events)
    clSqr20[y] = clSqr20[y] /(1.0*events)
    clErr20[y] = math.sqrt((clSqr20[y] - cl20[y]*cl20[y])/(1.0*events))
    cl30[y] = cl30[y] /(1.0*events)
    clSqr30[y] = clSqr30[y] /(1.0*events)
    clErr30[y] = math.sqrt((clSqr30[y] - cl30[y]*cl30[y])/(1.0*events))

print('Spectrum for full sky:')
for y in range(len(cl)):
    print(str(y)+'   '+str(cl[y])+"   "+str(clErr[y]))
print('Spectrum for |eta|<3.0:')
for y in range(len(cl)):
    print(str(y)+'   '+str(cl30[y])+"   "+str(clErr30[y]))
print('Spectrum for |eta|<2.0:')
for y in range(len(cl)):
    print(str(y)+'   '+str(cl20[y])+"   "+str(clErr20[y]))
print('Spectrum for |eta|<0.9:')
for y in range(len(cl)):
    print(str(y)+'   '+str(cl09[y])+"   "+str(clErr09[y]))


plt.yscale('log')
plt.plot(cl)
plt.savefig("powerSpectrum_iso.png")


