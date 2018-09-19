import sys
import subprocess as sp

#host_file = sys.argv[1] 
host_file = "hosts_run" 
to_kill = "root.exe"


inf = open(host_file)
ip_list = []
for line in inf:
	if line[0] == "#":
		continue
	if len(line) <= 1:
		continue 
	ip = line.split()[0]
	ip_list.append(ip)

for ip in ip_list:
	print ip
	sp.call(["ssh", ip, "killall", to_kill])
