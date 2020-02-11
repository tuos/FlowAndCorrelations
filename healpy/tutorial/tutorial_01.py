import matplotlib.pyplot as plt
#%matplotlib inline
import numpy as np
import healpy as hp

NSIDE = 32
print(
    "Approximate resolution at NSIDE {} is {:.2} deg".format(
        NSIDE, hp.nside2resol(NSIDE, arcmin=True) / 60
    )
)

NPIX = hp.nside2npix(NSIDE)
print(NPIX)

m = np.arange(NPIX)
#hp.mollview(m, title="Mollview image RING")
#hp.graticule()
SIZE = 400
DPI = 100
#hp.mollview(m, nest=False, xsize=SIZE, title="Mollview image RING")
hp.mollview(m, nest=False, xsize=SIZE, title="Mollview image RING")
plt.savefig("tutorial_nside32_ring.png", dpi=DPI)
hp.graticule()


vec = hp.ang2vec(np.pi / 2, np.pi * 3 / 4)
print(vec)

ipix_disc = hp.query_disc(nside=32, vec=vec, radius=np.radians(2))

m = np.arange(NPIX)
m[ipix_disc] = m.max()
#hp.mollview(m, title="Mollview image RING")
hp.mollview(m, nest=True, xsize=SIZE, title="Mollview image NEST")
hp.graticule()
plt.savefig("tutorial_nside32_nest_vec.png", dpi=DPI)


theta, phi = np.degrees(hp.pix2ang(nside=32, ipix=[0, 1, 2, 3, 4]))
print(theta)
print(phi)


wmap_map_I = hp.read_map("wmap_band_iqumap_r9_7yr_W_v4.fits")
#hp.write_map("my_map.fits", wmap_map_I, overwrite=True)
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

#fpdf.image("wmap_histeq_ecl.png", x = None, y = None, w = 0, h = 0, type = '', link = '')



