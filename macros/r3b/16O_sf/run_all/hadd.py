import subprocess as sp
import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("start", type=int)
parser.add_argument("end", type=int)
args = parser.parse_args()

def make_lst(start,end):
	out = []
	for i in range(start, end + 1):
		out.append("sim_{:04d}.root".format(i))
	return out

def hadd(lst, outf = "combo.root"):
	lst.insert(0,outf)
	lst.insert(0,"hadd")
	sp.call(lst)




if __name__ == "__main__":
	os.chdir("../runs/")
	hadd(make_lst(args.start,args.end))