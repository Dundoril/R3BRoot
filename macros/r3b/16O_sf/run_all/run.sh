mpirun -mca plm_rsh_no_tree_spawn 1 -display-allocation -hostfile hosts_run nice -n 10 python run_all.py
python read_tree.py