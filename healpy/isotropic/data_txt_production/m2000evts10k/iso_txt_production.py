
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


nside = 8
npix = hp.nside2npix(nside)
SIZE = 400
DPI = 100


cl = []
clSqr = []
clErr = []
for l in range(24):
   cl.append(0)
   clSqr.append(0)
   clErr.append(0)

indices2 = []
hpxmap2 = np.zeros(npix, dtype = np.float)
events = 10000
mult = 2000
arr = [[0 for i in range(mult)] for j in range(events)] 

outfile = open("data_txt_isofile_10k_2000m.txt","w")
outfile.write(str(events)+'\n')
for i in range(events):
    if i%50 == 0:
        print("First loop with i = "+str(i)+', and events = '+str(events))
    #print(i)
    #hpxmap2 = np.zeros(npix, dtype = np.float)
    outfile.write(str(i)+'   '+str(mult)+'   '+str(0)+'\n')
    for k in range(mult):
       ipix = random.randint(0, npix-1)
       arr[i][k] = hp.pix2ang(nside,ipix)
       #eta=-ln(tan(theta/2)), we want |eta|<2.4
       #this requires theta>0.18094062604 and theta<2.96065202755
       #a simple test shows that about 1% of particles are not in the theta range
       while (arr[i][k][0]<0.18094062604 or arr[i][k][0]>2.96065202755): 
          #print('%%% Not in |eta|<2.4, theta = '+str(arr[i][k][0])+', i = '+str(i)+', k = '+str(k))
          ipix = random.randint(0, npix-1)
          arr[i][k] = hp.pix2ang(nside,ipix)
       hpxmap2[ipix] += 1
       outfile.write(str("%.6f" % arr[i][k][0])+'   '+str("%.6f" % arr[i][k][1])+'\n')
       #if(arr[i][k][0]<0.18094062604 or arr[i][k][0]>2.96065202755): 
       #    print('???Not in |eta|<2.4, theta = '+str(arr[i][k][0]))
outfile.close()

'''
hpxmapFinal = np.zeros(npix, dtype = np.float)
for i in range(events): 
    if i%50 == 0:
        print('Second loop with i = '+str(i)+', and events = '+str(events))
    c = np.zeros(24)   
    hpxmapFinal = np.zeros(npix, dtype = np.float)
    hpxmap = np.zeros(npix, dtype = np.float)
    for k in range(mult):
       #print('arr[i][k] = '+str(arr[i][k]))
       indices = hp.ang2pix(nside,arr[i][k][0],arr[i][k][1])
       #print('i = '+str(i)+', indices = '+str(indices))
       #indices2.append(indices)
       hpxmap[indices] += 1

    for n in range(npix):
       if (hpxmap2[n] > 0):
          hpxmapFinal[n] += (hpxmap[n]/hpxmap2[n]) * (events)
       #if l == 0:
       #    print('i = '+str(i)+'   theta = '+str(arr[i][l][0]))

    c = hp.anafast(hpxmapFinal)
    #print(c)
    for x in range(len(c)):
       cl[x] = cl[x] + c[x]
       clSqr[x] = clSqr[x] + c[x]*c[x]

for y in range(len(cl)):
    #print(str(y)+'   '+str(cl[y])+"   "+str(clSqr[y]))
    cl[y] = cl[y] /(1.0*events)
    clSqr[y] = clSqr[y] /(1.0*events)
    clErr[y] = math.sqrt((clSqr[y] - cl[y]*cl[y])/(1.0*events))
    #print(str(y)+'   '+str(cl[y])+'   '+str(clSqr[y])+'   '+str(cl[y]*cl[y]))
    #clErr[y] = (clSqr[y] - cl[y]*cl[y])
#    print(str(y)+'   '+str(cl[y])+"   "+str(clErr[y]))

#print(cl)
#print(clErr)

outfilespec = open("txt_isofile_spectra.txt","w")
for y in range(len(cl)):
    outfilespec.write(str(y)+'   '+str(cl[y])+'   '+str(clErr[y])+'\n') 
outfilespec.close() 


plt.yscale('log')
plt.plot(cl)
plt.savefig("powerspect_iso2.png")
'''

