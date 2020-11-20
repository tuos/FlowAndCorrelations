
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


nside = 64
npix = hp.nside2npix(nside)
SIZE = 400
DPI = 100


hpxmap2 = np.zeros(npix, dtype = np.float)
hpxmap1 = np.zeros(npix, dtype = np.float)
hpxmapNorm = np.zeros(npix, dtype = np.float)

with open("/scratch/anderht3/cent0_total.txt") as inputFile:
    firstLine = inputFile.readline()
    lines = inputFile.readlines()
#print("read file")
events = int(firstLine)
thetas = []
phis = []
thetas2 = []
phis2 = []


#events = 200

i = 0
for x in range(events):
   i += 1
   j = x+1
   if x%100 == 0:
      print("First loop, event ", x, " processed")
   while i < len(lines) and len(lines[i].split())< 3 and float(lines[i].split()[0]) != j:
       thetas.append(float(lines[i].split()[0]))
       phis.append(float(lines[i].split()[1]))
       if j == 1:
           thetas2.append(float(lines[i].split()[0]))
           phis2.append(float(lines[i].split()[1]))
       i += 1

indices = hp.ang2pix(nside, thetas, phis)
indices2 = hp.ang2pix(nside, thetas2, phis2)

for l in range(len(thetas)):
   hpxmap2[indices[l]] += 1.0/events/7694
for l in range(len(thetas2)):
   hpxmap1[indices2[l]] += 1.0/len(thetas2)

print(len(thetas2))

for i in range(npix):
    if hpxmap2[i] != 0:
        hpxmapNorm[i] = hpxmap1[i]*1.0/hpxmap2[i]

#hp_smoothed = hp.sphtfunc.smoothing(hpxmap2, fwhm=np.radians(1), iter = 1)

hp_smoothed = hp.smoothing(hpxmapNorm, fwhm=np.radians(5))

#hp.mollview(hp_smoothed, cmap = cm.jet, xsize = SIZE, min = 0.9, max = 1.1, title='Isotropic smoothed 1 event with normalization')
#hp.mollview(hp_smoothed, cmap = cm.jet, xsize = SIZE, title='AMPT PbPb 5 TeV 0-5% $|\eta|<2.4$, smoothed single event normalized with all events')
hp.mollview(hp_smoothed, cmap = cm.jet, xsize = SIZE, min = 0, max = 3.0, title='AMPT PbPb 5 TeV 0-5% $|\eta|<2.4$, smoothed single event normalized with all events')

hp.graticule()
plt.savefig("map_ampt_smooth_single.png", dpi = DPI)


