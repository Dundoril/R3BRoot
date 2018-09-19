import glob
import os
import sys
sys.path.append('/home/sfiebiger/Documents/progtest/neutron_scatter/mpi4py_map-master/mpi4py_map/')
import mpi4py
import mpi4py_map
import subprocess as sp
import time



def run(sim_file):
    sp.call(["root", "-l", "-q", "-b", "{}".format(sim_file)])

def run2(sim_file):
	xx = 500
	for i in range(xx):
		for j in range(xx):
			for k in range(xx):
				i*j*k

if __name__ == "__main__":
	os.chdir("../runs")
	files = glob.glob("run_sim*.C")
	print files
	mpi4py_map.map(run, files)
