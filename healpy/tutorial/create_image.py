import healpy as hp
import numpy as np
import matplotlib.pyplot as plt

SIZE = 400
DPI = 60


m = np.arange(hp.nside2npix(32))
hp.mollview(m, nest=True, xsize=SIZE, title="Mollview image NESTED")
plt.savefig("moll_nside32_nest.png", dpi=DPI)

hp.mollview(m, nest=False, xsize=SIZE, title="Mollview image RING")
plt.savefig("moll_nside32_ring.png", dpi=DPI)

'''
wmap_map_I = hp.read_map("./wmap_band_iqumap_r9_7yr_V_v4_udgraded32.fits")

hp.mollview(
    wmap_map_I,
    coord=["G", "E"],
    title="Histogram equalized Ecliptic",
    unit="mK",
    norm="hist",
    min=-1,
    max=1,
    xsize=SIZE,
)
hp.graticule()

plt.savefig("./wmap_histeq_ecl.png", dpi=DPI)


mask = hp.read_map(
    "./wmap_temperature_analysis_mask_r9_7yr_v4_udgraded32.fits"
).astype(np.bool)
wmap_map_I_masked = hp.ma(wmap_map_I)
wmap_map_I_masked.mask = np.logical_not(mask)
LMAX = 1024
cl = hp.anafast(wmap_map_I_masked.filled(), lmax=LMAX)
ell = np.arange(len(cl))
plt.figure()
plt.plot(ell, ell * (ell + 1) * cl)
plt.xlabel("ell")
plt.ylabel("ell(ell+1)cl")
plt.grid()

plt.savefig("./wmap_powspec.png", dpi=DPI)
'''
