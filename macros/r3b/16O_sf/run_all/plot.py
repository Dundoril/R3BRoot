

def get_width_offset(geoname):
	path = "../../geo/"+geoname
	with open(path) as inf:
		for line in inf:
			if "Float_t" in line and "fiber_thickness" in line and not "air_layer" in line and not "fiber_nbr" in line:
				fthick = float((line.split("=")[-1]).split(";")[0])
			if "Int_t" in line and "fiber_nbr" in line and not "air_layer" in line and not "fiber_thickness" in line:
				fnbr = float((line.split("=")[-1]).split(";")[0])
			if "Float_t" in line and "air_layer" in line and not "fiber_nbr" in line:
				air =float((line.split("=")[-1]).split(";")[0])
				break
	return fnbr*fthick*(1+air) / 2.

def plot(det):
	import os
	import glob
	import matplotlib.pyplot as plt

	if det == 3:
		run_sim_var = "fi3Distance"
		fi_0 = "Fi3a"
		fi_1 = "Fi3b"
		distance_offset = get_width_offset("create_fi3a_geo.C")
	if det == 7:
		run_sim_var = "fi7_8Distance"
		fi_0 = "Fi7"
		fi_1 = "Fi8"
		distance_offset = get_width_offset("create_fi7_geo.C")
	if det == 10:
		run_sim_var = "fi10_11Distance"
		fi_0 = "Fi10"
		fi_1 = "Fi11"
		distance_offset = get_width_offset("create_fi10_geo.C")
	total = 0

	run_files = sorted(glob.glob("../runs/run_sim*.C"))
	x_vals = []
	for rf in run_files:
		with open(rf) as inf:
			for line in inf:
				if "Double_t" in line and run_sim_var in line:
					valx = (line.split("=")[-1]).split(";")[0]
					x_vals.append(float(valx)- distance_offset)
					break

	out_files = sorted(glob.glob("../runs/entries/sim*.dat"))
	y_vals_0 = []
	y_vals_1 = []

	for of in out_files:
		with open(of) as inf:
			for line in inf:
				if "total events" in line:
					total = float(line.split(":")[1])
				if fi_0 in line:
					valy_0 = float(line.split(":")[1])
				if fi_1 in line:
					valy_1 = float(line.split(":")[1])
			y_vals_0.append((valy_0 / float(total))*1)
			y_vals_1.append((valy_1 / float(total))*1)
	f, ax = plt.subplots(2, figsize = (16, 9))

	ax[0].set_xlabel("Total Distance / cm")
	ax[1].set_xlabel("Total Distance / cm")
	ax[0].set_ylabel("Counts")
	ax[1].set_ylabel("Counts")
	ax[0].set_yscale("log")
	ax[1].set_yscale("log")
	# print x_vals ,y_vals_1
	ax[0].plot(x_vals, y_vals_0, label = fi_0, marker = 'o', markersize = 3)
	ax[1].plot(x_vals, y_vals_1, label = fi_1)

	ax[0].axhline(1e-4, 0.005, color = "darkred", alpha = 0.5, linestyle = "--")
	ax[1].axhline(1e-4, 0.005, color = "darkred", alpha = 0.5, linestyle = "--")

	ax[0].set_ylim((1e-6, 1))
	ax[1].set_ylim((1e-6, 1))

	

	ax[0].legend(loc = "upper right")
	ax[1].legend(loc = "upper right")

	# plt.show()
	plt.savefig("det_{}.pdf".format(det))
	
	with open("det_{}.dat".format(det), "w") as outf:
		for i, el in enumerate(x_vals):
			outf.write("{}	{}	{}\n".format(x_vals[i], y_vals_0[i], y_vals_1[i]))


if __name__ == "__main__":
	plot(3)
	plot(7)
	plot(10)