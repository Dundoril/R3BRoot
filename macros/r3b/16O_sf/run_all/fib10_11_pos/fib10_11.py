import glob
import matplotlib.pyplot as plt
import ROOT
import numpy as np
from scipy.optimize import curve_fit

class GetHisto():
	"""
	Returns specific ROOT histogram from *.root file
	"""
	def __init__(self,filepath, histoname):
		self.filepath = filepath
		self.in_file = ROOT.TFile(self.filepath)
		self.hname = histoname
		self.histo = ROOT.gROOT.FindObject(self.hname)
		

	def out(self):
		return self.histo

def histo_to_np(histo, err = False):
	"""
	Makes two numpy arrays (x-axis,y-axis) from ROOT histogram.
	
	Returns list of arrays: [x, y]
	"""
	x = []
	y = []
	errx = []
	erry = []
	for bin_ in range(0, histo.GetNbinsX() + 1):
		x.append(histo.GetBinCenter(bin_))
		y.append(histo.GetBinContent(bin_))
		if err == True:
			errx.append(histo.GetBinWidth(bin_) / 2.)
			erry.append(histo.GetBinError(bin_))
	if err == True:
		return [np.asarray(x), np.asarray(y), np.asarray(errx), np.asarray(erry)]
	else:
		return [np.asarray(x), np.asarray(y)]


flst = sorted(glob.glob("*.root"))

h10 = []

for file_ in flst:
	hist_inst = GetHisto(file_, "Fi10Point.fX")
	hist = hist_inst.out()
	h10.append(histo_to_np(hist))



f, ax = plt.subplots(nrows = 3, figsize = (16, 12))

def funcp4(x, a, b, c, d, e):
		return a * x**4 + b * x**3 + c * x**2 + d * x + e

def gfunc(x,a,b,c):
	return a*np.exp(-0.5*((x-b)/c)**2)

func = gfunc

fit_pars = []

for i, el in enumerate(h10):
	# if not i == 9:
	# 	continue
	
	x_corr = h10[i][0][np.argwhere(h10[i][1] > 200)[0][0]]
	x_data_t = (h10[i][0] - x_corr)
	y_data = h10[i][1][(x_data_t >= 0)]
	x_data = x_data_t[(x_data_t >= 0)]
	ax[0].plot(x_data, y_data, label = "fi10_11Distance = {}".format(330 + i*10))
	ax[0].legend(loc = "upper right")


	# popt, pcov = curve_fit(func, x_data, y_data, bounds = [(-np.inf, 0,-np.inf),(np.inf, 0.5, np.inf)])
	popt, pcov = curve_fit(func, x_data, y_data)
	fit_pars.append(popt)

	ax[1].plot(x_data, func(x_data, *fit_pars[i]), label = "fi10_11Distance = {}".format(330 + i*10))


	poitns = np.linspace(0,3, 10000)
	new_data = func(x_data, *fit_pars[i])
	max_val = np.max(new_data)
	offsets =  x_data[np.where(new_data == max_val)]

	ax[2].axhline(0, 0.005, color = "darkred", alpha = 0.5, linestyle = "--", zorder = -1)
	ax[2].plot(330+i*10, offsets, marker = "o")

	print 330+i*10, offsets

	ax[0].set_xlim([-1,3])
	ax[1].set_xlim([-1,3])
	ax[2].set_ylim([-0.5,0.5])

	ax[0].set_xlabel("Corrected x-pos / cm")
	ax[0].set_ylabel("Counts")
	ax[1].set_xlabel("Corrected x-pos / cm")
	ax[1].set_ylabel("Counts")
	ax[2].set_xlabel("Distance form 18 deg point / cm")
	ax[2].set_ylabel("Maximum count position / cm")


plt.show()
# plt.savefig("fib10_11_pos.pdf")