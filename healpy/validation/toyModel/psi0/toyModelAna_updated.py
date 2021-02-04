import sys
import healpy as hp
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
import scipy.special as spc
import math
from scipy.special import lpmn
import scipy.integrate as integrate
from scipy.integrate import quad
from numpy import sin, cos


nside = 8
npix = hp.nside2npix(nside)

#with open("/store/user/tuos/angular_power_spectrum_HI/toyModel/flowOnly/cent2/txt_toyModel_cent2.txt") as inputFile:
#with open("/store/user/tuos/healpy/toyModel/steg10_m2000_flow08/txt_toyModel_10kevts_m2000_08flow.txt") as inputFile:

#with open("/store/user/tuos/healpy/toyModel/steg10_m2000_flow08/psi_random/txt_toyModel_10kevts_m2000_08flow_PsiRandom_SetSeed.txt") as inputFile:
with open("/store/user/tuos/healpy/toyModel/steg10_m2000_flow08/txt_toyModel_10kevts_m2000_08flow_Psi0_SetSeed.txt") as inputFile:
    firstLine = inputFile.readline()
    lines = inputFile.readlines()
#print("read file")
events = int(firstLine)
thetas = []
phis = []

events = 10000

i = 0
for x in range(events):
   i += 1
   j = x+1
   if x%100 == 0:
      print("First loop, event ", x, " processed")
   while i < len(lines) and len(lines[i].split())< 3 and float(lines[i].split()[0]) != j:
       thetas.append(float(lines[i].split()[0]))
       phis.append(float(lines[i].split()[1]))
       i += 1
indices = hp.ang2pix(nside, thetas, phis)
hpxmap2 = np.zeros(npix, dtype = np.float)

for l in range(len(thetas)):
   hpxmap2[indices[l]] += 1.0
#print("total map made")
clFinal = np.zeros(24)
cl2Final = np.zeros(24)
clSqr = np.zeros(24)
clErr = np.zeros(24)
cl2Sqr = np.zeros(24)
cl2Err = np.zeros(24)
i = 0
for x in range(events):
   i += 1
   j = x+1
   thetas2 = []
   phis2 = []
   if x%100 == 0:
      print("Second loop, event ", x, " processed")
   while i < len(lines) and len(lines[i].split())< 3 and float(lines[i].split()[0]) != j: 
      thetas2.append(float(lines[i].split()[0]))
      phis2.append(float(lines[i].split()[1]))
      i+=1
   
   indices2 = hp.ang2pix(nside, thetas2, phis2)
   hpxmap = np.zeros(npix, dtype = np.float)
   for k in range(len(thetas2)):
      hpxmap[indices2[k]] += 1.0
      #hpxmap[indices[k]] += npix*(1.0/len(thetas))
   hpxmapFinal = np.zeros(npix, dtype = np.float)

#   for v in range(len(thetas)):
#      hpxmapFinal[indices[v]] += (hpxmap[indices[v]]/hpxmap2[indices[v]]) * (npix*(1.0/len(thetas2)))
   for n in range(npix):
      if (hpxmap2[n] > 0):
         hpxmapFinal[n] += (hpxmap[n]/hpxmap2[n]) * (events)

   c = hp.anafast(hpxmapFinal)
   alm = hp.map2alm(hpxmapFinal, lmax = 23)
   #print(c)
   #print()
   cl2 = []
   for g in range(24):
     cl2.append(c[g] - (1.0/(2*g+1)*((abs(alm[g]))**2)))
   #print(cl2)
   for l in range(24):
     clFinal[l] = clFinal[l] + c[l]
     cl2Final[l] = cl2Final[l] + cl2[l]
     clSqr[l] = clSqr[l] + c[l]*c[l]
     cl2Sqr[l] = cl2Sqr[l] + cl2[l]*cl2[l]
for k in range (24):
   clFinal[k] = clFinal[k] / (1.0*events)
   cl2Final[k] = cl2Final[k] / (1.0*events)
   clSqr[k] = clSqr[k]/ (1.0*events)
   cl2Sqr[k] = cl2Sqr[k]/ (1.0*events)
   clErr[k] = math.sqrt((clSqr[k] - clFinal[k]*clFinal[k])/(1.0*events))
   cl2Err[k] = math.sqrt((cl2Sqr[k] - cl2Final[k]*cl2Final[k])/(1.0*events))
   print(k,clFinal[k],clErr[k])
#print()
#print()
for k in range (24):
    print(k,cl2Final[k],cl2Err[k])
#print()
#print(clFinal)

outfilecl = open("results_cl_spectra.txt","w")
for y in range(len(clFinal)):
    outfilecl.write(str(y)+'   '+str(clFinal[y])+'   '+str(clErr[y])+'\n')
outfilecl.close()

outfilecl2 = open("results_cl2_spectra.txt","w")
for y in range(len(cl2)):
    outfilecl2.write(str(y)+'   '+str(cl2Final[y])+'   '+str(cl2Err[y])+'\n')
outfilecl2.close()

plt.yscale('log')
plt.plot(clFinal)
plt.savefig("powerspect_updated.png")


