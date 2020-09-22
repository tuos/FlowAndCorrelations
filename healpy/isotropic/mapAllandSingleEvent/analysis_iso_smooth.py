
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
events = 8000
mult = 2500
for i in range(events):
    for k in range(mult):
       ipix = random.randint(0, npix-1)
       #hpxmap2[indices2[i]] += 1.0
       hpxmap2[ipix] += npix*1.0/mult/events


#hp_smoothed = hp.sphtfunc.smoothing(hpxmap2, fwhm=np.radians(1), iter = 1)

hp.mollview(hpxmap2, cmap = cm.jet, xsize = SIZE, min = 0.9, max = 1.1, title='Isotropic randomised')

hp.graticule()
plt.savefig("map_iso_smooth_all.png", dpi = DPI)


