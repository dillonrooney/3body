#!/bin/sh
#SBATCH -n 256            # 8 CPU cores
#SBATCH -t 0-00:5:00   # 30 minutes
#SBATCH -p compute      # partition name
#SBATCH -J 1000particles     # sensible name for the job

#100, 125, 200, 250, 

# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/naive

# launch the code
echo "compare"
echo "1000 particles"
echo "250 core checking"
time mpirun -n 250 bin/naive check1000.init
echo "125 core checking"
time mpirun -n 125 bin/naive check1000.init
echo "200 core checking"
time mpirun -n 200 bin/naive check1000.init
echo "250 core checking"
time mpirun -n 100 bin/naive check1000.init
echo "80 core checking"
time mpirun -n 80 bin/naive check1000.init
