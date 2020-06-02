import healpy as hp
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

# Set the number of sources and the coordinates for the input
nsources = int(2664001)
nside = 8
npix = hp.nside2npix(nside)

# Coordinates and the density field f
#thetas = np.random.random(nsources) * np.pi
#phis = np.random.random(nsources) * np.pi * 2.

#fs = np.random.randn(nsources)

with open("eventFile5.txt") as inputFile:
    firstLine = inputFile.readline()
    lines = inputFile.readlines()
    #print (lines[1].split()[1])
cl = []
for l in range(24):
   cl.append(0)
events = int(firstLine)
#print(len(lines))
i = 0
for x in range(events):
    cTot = []
    i += 1
    j = x+1
    phis = []
    thetas = []
    while i < len(lines) and float(lines[i].split()[0]) != j:
      # print(lines[i].split()[0])
      #print(lines[i+1].split()[0])
      thetas.append(float(lines[i].split()[1]))
      phis.append(float(lines[i].split()[2]))
      i+=1

    indices = hp.ang2pix(nside, thetas, phis)
    hpxmap = np.zeros(npix, dtype = np.float)
    for k in range(len(thetas)):
      hpxmap[indices[k]] += npix*(1.0/len(thetas))
    c = hp.anafast(hpxmap)
    cV = c
    for z in range(len(cV)):
      cl[z] = cl[z] + cV[z]
for c in range(len(cl)):
    cl[c] = cl[c] / (1.0*events)
cOdd = []

for c in range(11):
   cOdd.append(cl[c*2+1])
plt.xscale('log')
plt.yscale('log')
plt.plot(cOdd)
plt.savefig("powerspect_ODD.png")

