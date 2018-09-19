import root_numpy
import ROOT 
import numpy as np
import glob
import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("-c", "--combo", action="store_true")
args = parser.parse_args()

def hold():
	"""
	Pauses the program at this positions.
	"""
	print "\n"
	inp = raw_input("Holding. Enter 'a' to abort, Press 'Enter' to continue: ")
	if inp == "a":
		raise SystemExit("Manuel Abort.")

def root_show(histo, mode = "draw", outname = "out.root"):
	"""
	Chosse to draw a ROOT histo or save it to file.

	Parameters:
		histo: root histogram or list of histograms
			Input ROOT histo or list of histos
		mode: str, optional
			Modes are 'draw' or 'save'
		outname: str, optional
			The name of the output ROOT file
	"""
	if mode == "draw":
		if type(histo) == list:
			print "You can draw only a histogram, not a list!"
		else:
			histo.Draw()
			hold()
	if mode == "save":
		outfile = ROOT.TFile(outname,"RECREATE")
		if type(histo) == list:
			for h in histo:
				h.Write()
		else:
			histo.Write()
		outfile.Close()

def tree_data(br):
	# convert tree or branches of tree
	br_keys = sorted(br.keys())
	array = root_numpy.tree2array(intree, branches = br_keys)

	# read branch data and convert to flat np arr
	data = {}
	for el in br:
		data[el] = np.hstack(array[el].flat)
	# data =  np.hstack(array['dTOFPoint.fPx'].flat)

	return data

def tree_data_cut(br):
	# convert tree or branches of tree
	data = {}
	br_keys = sorted(br.keys())
	for det in br_keys:
		print "	Branch:", det
		array = root_numpy.tree2array(intree, branches = [det],\
		object_selection={'{}.fELoss > {}'.format(det.split(".")[0], branches[det]) : [det]})
		data[det] = np.hstack(array[det].flat)
	# read branch data and convert to flat np arr
	

	# data =  np.hstack(array['dTOFPoint.fPx'].flat)

	return data

def make_histos(data, cut = False):
	# make histo(s)
	hists = []
	for el in data:
		if len(data[el]) > 0:
			min_val = np.min(data[el])
			max_val = np.max(data[el])
		else:
			min_val = 0
			max_val = 1
		if cut == True:
			title = "{} (ELoss > {})".format(el, branches[el])
		else:
			title = el
		hist = ROOT.TH1D(el, title, 10000, np.floor(min_val) - 1, np.ceil(max_val)+1)
		root_numpy.fill_hist(hist, data[el])
		hists.append(hist)

	return hists

def get_entries(data, mode = "p"):
	if mode == "w":
		ensure_dir_silent("entries")
		outfile = open("entries/{}.dat".format(filename.split(".")[0]), "w")
		outfile.write("total events:	{}\n".format(tree_entries))
	for el in data:
		if mode == "p":
			print el, len(data[el])
		elif mode == "w":
			outfile.write("{}:	{}\n".format(el, len(data[el])))
	if mode == "w":
		outfile.close()

def ensure_dir_silent(dir_name):
	"""
	Creates a directory with name 'dir_name'.
	"""
	import os
	if not os.path.isdir(dir_name):
		os.makedirs(dir_name) 

if __name__ == "__main__":
	# open file and load tree
	home_path = os.getcwd()
	os.chdir("../runs")
	if args.combo == True:
		sim_files = ["combo.root"]
	else:
		sim_files = sorted(glob.glob("sim*.root"))
	sim_files = ["sim_9999.root"]
	for i, file_ in enumerate(sim_files):
		os.chdir("../runs")
		filename = file_
		rfile = ROOT.TFile(filename)
		intree = rfile.Get('evt')
		tree_entries = intree.GetEntries()
		print filename, "Events in 'evt' Tree:", tree_entries

		branches = {"Fi3aPoint.fX" :  0.0021,
		            "Fi3bPoint.fX" : 0.0021,
				    "Fi7Point.fX"  : 0.01,
				    "Fi8Point.fX"  : 0.01,
				    "Fi10Point.fX" : 0.005,
				    "Fi11Point.fX" : 0.005,
				    "dTOFPoint.fX" : 0}
		# data = tree_data(branches)
		data = tree_data_cut(branches)
		# get_entries(data, mode = "w")
		# hists = make_histos(data)
		hists = make_histos(data, cut = True)

		# # # show
		# root_show(hists[0], mode = "draw")
		fname = os.path.basename(file_).split(".")[0] + "_out.root"
		os.chdir(home_path)
		root_show(hists, mode = "save", outname = fname)


