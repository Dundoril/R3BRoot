import os
import random

os.chdir("../")

class SimFiles():
	"""
	distanceZeroMagnet: Abstand Target -> 18 deg Knickpunkt
	fi7_8DistanceMagnetDetectors: Abstand Knickpunkt -> Detektor Mitte
	fi10_11DistanceMagnetDetectors: Abstand Knickpunkt -> Detektor Mitte

	Scnittpunkt Beam -> GLAD Ausgang: 248.627

	"""
	def __init__(self, master_file):
		self.width_3a_3b = self._get_width_offset("create_fi3a_geo.C")
		self.width_7_8 = self._get_width_offset("create_fi7_geo.C")
		self.width_10_11 = self._get_width_offset("create_fi10_geo.C")
		
		self.file_data = []

		self.line_outFile = ""
		self.line_parFile = ""
		self.line_distanceZeroDet = 0.0
		self.line_fi3Distance = 0.0
		self.line_distanceZeroMagnet = 0.0
		self.line_fi7_8Distance = 0.0
		self.line_fi7_8DistanceMagnetDetectors = 0.0
		self.line_fi10_11Distance = 0.0
		self.line_fi10_11DistanceMagnetDetectors = 0.0
		self.line_dTof_DistanceMagnetDetectors = 0.0
		self.line_dTof_offset = 0.0
		self.line_distanceZeroTarget = 0.0
		self.line_fieldScale = 0.0
		self.line_nEvents = 0
		self.line_func_name = 0
		self.line_fi10_11AbsoluteOffset = 0
		self.line_randomSeed = 0
		self.line_target_type = ""
		self.line_target_type_orig = ""
		self.line_target_change = ""
		
		self._read_master(master_file)
		self.file_name = "run_sim.C"
		
		
		
	# misc
	def _get_width_offset(self, geoname):
		path = "../geo/"+geoname
		with open(path) as inf:
			for line in inf:
				if "Float_t" in line and "fiber_thickness" in line and not "air_layer" in line and not "fiber_nbr" in line:
					fthick = self._split_line(line)
				if "Int_t" in line and "fiber_nbr" in line and not "air_layer" in line and not "fiber_thickness" in line:
					fnbr = self._split_line(line)
				if "Float_t" in line and "air_layer" in line and not "fiber_nbr" in line:
					air = self._split_line(line)
					break
		return fnbr*fthick*(1+air) / 2.
			


	def _read_master(self, master):
		with open(master) as inf:
			for line in inf:
				if "Double_t" in line and "distanceZeroDet" in line:
					self.line_distanceZeroDet = self._read_val_line(line)
					self.file_data.append(["distanceZeroDet"])
				elif "Double_t" in line and "fi3Distance" in line:
					self.line_fi3Distance = self._read_val_line(line)
					self.file_data.append(["fi3Distance"])
				elif "Double_t" in line and "distanceZeroMagnet" in line:
					self.line_distanceZeroMagnet = self._read_val_line(line)
					self.file_data.append(["distanceZeroMagnet"])
				elif "Double_t" in line and "fi7_8Distance" in line and not "fi7_8DistanceMagnetDetectors" in line:
					self.line_fi7_8Distance = self._read_val_line(line)
					self.file_data.append(["fi7_8Distance"])
				elif "Double_t" in line and "fi7_8DistanceMagnetDetectors" in line:
					self.line_fi7_8DistanceMagnetDetectors = self._read_val_line(line)
					self.file_data.append(["fi7_8DistanceMagnetDetectors"])
				elif "Double_t" in line and "fi10_11Distance" in line and not "fi10_11DistanceMagnetDetectors" in line:
					self.line_fi10_11Distance = self._read_val_line(line)
					self.file_data.append(["fi10_11Distance"])
				elif "Double_t" in line and "fi10_11DistanceMagnetDetectors" in line:
					self.line_fi10_11DistanceMagnetDetectors = self._read_val_line(line)
					self.file_data.append(["fi10_11DistanceMagnetDetectors"])
				elif "Double_t" in line and "dTof_DistanceMagnetDetectors" in line:
					self.line_dTof_DistanceMagnetDetectors = self._read_val_line(line)
					self.file_data.append(["dTof_DistanceMagnetDetectors"])
				elif "Double_t" in line and "dTof_offset" in line:
					self.line_dTof_offset = self._read_val_line(line)
					self.file_data.append(["dTof_offset"])
				elif "Double_t" in line and "distanceZeroTarget" in line:
					self.line_distanceZeroTarget = self._read_val_line(line)
					self.file_data.append(["distanceZeroTarget"])
				elif "Double_t" in line and "fi10_11AbsoluteOffset" in line:
					self.line_fi10_11AbsoluteOffset = self._read_val_line(line)
					self.file_data.append(["fi10_11AbsoluteOffset"])
				elif "Float_t" in line and "fieldScale" in line:
					self.line_fieldScale = self._read_val_line(line)
					self.file_data.append(["fieldScale"])
				elif "Int_t" in line and "nEvents" in line:
					self.line_nEvents = self._read_val_line(line)
					self.file_data.append(["nEvents"])
				elif "Int_t" in line and "randomSeed" in line:
					self.line_randomSeed = int(self._read_val_line(line))
					self.file_data.append(["randomSeed"])
				elif "TString outFile" in line:
					self.line_outFile = self._split_line(line, to_float = False)
					self.file_data.append(["outFile"])
				elif "TString parFile" in line:
					self.line_parFile = self._split_line(line, to_float = False)
					self.file_data.append(["parFile"])
				elif "targetType" in line and ".geo.root" in line and not "//" in line:
					self.line_target_type = line
					self.line_target_type_orig = line
					self.file_data.append(["targetType"])
				else:
					self.file_data.append(line)
	
	def _split_line(self, line_str, to_float = True):
		line = (line_str.split("=")[-1]).split(";")[0]
		if to_float ==True:
			return float(line)
		else:
			return line
	
	def _return_str(self, var_name, val):
		if type(val) == float:
			ftype = "Double_t"
		elif type(val) == int:
			ftype = "Int_t"
		elif type(val) == str:
			ftype = "TString"
			val = '"{}"'.format(val)

		return "    {} {} = {};\n".format(ftype, var_name, val)
	
	def make_file(self, fname = None):
		if fname == None:
			fname = self.file_name
		with open(fname, "w")as outf:
			for i, el in enumerate(self.file_data):
				# print el
				if "void" in el:
					outf.write("void run_sim_{:04d}()\n".format(self._vars("func_name")))
				elif type(el) == list:
					if el[0] == "targetType":
						# print self._vars("targetType")
						outf.write(self._vars("targetType"))
					else:
						outf.write(self._return_str(el[0], self._vars(el[0])))
				else:
					outf.write(self.file_data[i])
	
	def _vars(self, in_var):
		self.var_dic = {"distanceZeroDet": self.line_distanceZeroDet,
		                "fi3Distance": self.line_fi3Distance,
		                "distanceZeroMagnet": self.line_distanceZeroMagnet,
		                "fi7_8Distance": self.line_fi7_8Distance,
		                "fi7_8DistanceMagnetDetectors": self.line_fi7_8DistanceMagnetDetectors,
		                "fi10_11Distance": self.line_fi10_11Distance,
		                "fi10_11DistanceMagnetDetectors": self.line_fi10_11DistanceMagnetDetectors,
		                "outFile" : self.line_outFile,
		                "parFile" : self.line_parFile,
		                "dTof_DistanceMagnetDetectors": self.line_dTof_DistanceMagnetDetectors,
		                "dTof_offset": self.line_dTof_offset,
						"distanceZeroTarget": self.line_distanceZeroTarget,
						"fieldScale": self.line_fieldScale,
						"nEvents": self.line_nEvents,
						"func_name": self.line_func_name,
						"targetType": self.line_target_type,
						"fi10_11AbsoluteOffset" : self.line_fi10_11AbsoluteOffset,
						"randomSeed" : self.line_randomSeed,
		}
		return self.var_dic[in_var]
	
	def _read_val_line(self, f_line):
		return self._split_line(f_line)

	# vars
	def set_distanceZeroDet(self, val):
		self.line_distanceZeroDet = float(val)
		
	def set_fi3Distance(self, val):
		self.line_fi3Distance = float(val) + self.width_3a_3b
		
	def set_distanceZeroMagnet(self, val):
		self.line_distanceZeroMagnet = float(val)
		
	def set_fi7_8Distance(self, val):
		self.line_fi7_8Distance = float(val) + self.width_7_8
		
	def set_fi7_8DistanceMagnetDetectors(self, val):
		self.line_fi7_8DistanceMagnetDetectors = float(val)
		
	def set_fi10_11Distance(self, val):
		self.line_fi10_11Distance = float(val) + self.width_10_11
		
	def set_fi10_11DistanceMagnetDetectors(self, val):
		self.line_fi10_11DistanceMagnetDetectors = float(val)
	
	def set_dTof_DistanceMagnetDetectors(self, val):
		self.line_dTof_DistanceMagnetDetectors = float(val)
		
	def set_dTof_offset(self, val):
		self.line_dTof_offset = float(val)

	def set_distanceZeroTarget(self, val):
		self.line_distanceZeroTarget = float(val)

	def set_fieldScale(self, val):
		self.line_fieldScale = float(val)

	def set_fi10_11AbsoluteOffset(self, val):
		self.line_fi10_11AbsoluteOffset = float(val)

	def set_nEvents(self, val):
		self.line_nEvents = int(val)

	def set_randomSeed(self, val):
		self.line_randomSeed = int(val)
	
	def set_outFile(self, val):
		self.line_outFile =val
	
	def set_parFile(self, val):
		self.line_parFile =val
	
	def set_func_name(self, val):
		self.line_func_name = val
	
	def set_targetType(self, val):
		if self.line_target_change == val:
			pass
		else:
			self.line_target_type = self.line_target_type_orig.replace(".geo.root", "_{}.geo.root".format(val))
			self.line_target_change = val

def ensure_dir_silent(dir_name):
	"""
	Creates a directory with name 'dir_name'.
	"""
	import os
	if not os.path.isdir(dir_name):
		os.makedirs(dir_name) 

def linspace(start,end,step):
	lst = [start]
	temp = start
	while temp < end:
		temp += step
		lst.append(temp)
	if not end in lst:
		lst.append(end)
	return lst

if __name__ == "__main__":
	run_folder = "runs"
	# output_folder = "out"
	ensure_dir_silent(run_folder)
	# ensure_dir_silent(output_folder)

	sim_inst = SimFiles("run_sim_master.C")
	file_nbr = 0
	

	tt = ["0mg","50mg","100mg","150mg","200mg"]
	for i in range(len(tt)):
		## file parameter
		sim_inst.set_nEvents(1000000)
		sim_inst.set_outFile(os.path.join("sim_{:04d}.root".format(file_nbr)))
		sim_inst.set_parFile(os.path.join("par_{:04d}.root".format(file_nbr)))
		sim_inst.set_func_name(file_nbr)
		# sim_inst.set_randomSeed(random.randint(100000,999999))

		## Target
		# sim_inst.set_distanceZeroTarget(10)
		sim_inst.set_targetType(tt[i])

		## Magnet
		# sim_inst.set_fieldScale(-0.601)

		## detector parameter
		#Det 3a/3b
		# sim_inst.set_distanceZeroDet(1)
		# sim_inst.set_fi3Distance(1.2)

		#Det 7/8
		# sim_inst.set_distanceZeroMagnet(3)
		# sim_inst.set_fi7_8Distance(13.5)
		# sim_inst.set_fi7_8DistanceMagnetDetectors(5)

		#Det 10/11
		# sim_inst.set_fi10_11Distance(11.0)
		# sim_inst.set_fi10_11DistanceMagnetDetectors(400)
		# sim_inst.set_fi10_11AbsoluteOffset(0.33)

		#Det dTOF
		# sim_inst.set_dTof_DistanceMagnetDetectors(8)
		# sim_inst.set_dTof_offset(9)

		sim_inst.make_file(fname = os.path.join(run_folder, "run_sim_{:04d}.C".format(file_nbr)))
		file_nbr += 1
