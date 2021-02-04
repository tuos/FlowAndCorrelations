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


with open("../isotropic/results_cl2_spectra.txt") as inputFile:
   clIso0 = inputFile.readlines()

with open("../toyModel/results_cl2_spectra.txt") as inputFile2:
   cl0 = inputFile2.readlines()


c0 = np.zeros(24)


#b11 = math.sqrt((2*1+1)/(4*math.pi)*1/math.factorial(2))* -1.56727

b00 = math.sqrt((2*0+1)/(4*math.pi)*1/math.factorial(0))* -1.9696

b22 = math.sqrt((2*2+1)/(4*math.pi)*1/math.factorial(4))* -3.99

#b33 = math.sqrt((2*3+1)/(4*math.pi)*1/math.factorial(6))* -17.6705
for i in range(24):
   #c0[i] += (float(cl0[i].split()[1]))
   c0[i] += (float(cl0[i].split()[1]) - float(clIso0[i].split()[1]))

v2 = np.zeros(10)

a = (5/2)*c0[2]/(abs(b22)**2)*(abs(b00))**2/(4*math.pi)
v2[0] += math.sqrt(abs(a))


for x in range(1):
   print(x,v2[x])
#plt.plot(v2)
#plt.axis([0,10,0,0.05])
#plt.savefig("v2.png")
