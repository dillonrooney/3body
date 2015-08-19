#!/bin/sh
#SBATCH -n 64            # 8 CPU cores
#SBATCH -t 0-00:5:00   # 30 minutes
#SBATCH -p compute      # partition name
#SBATCH -J 1000particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/naive

# launch the code
echo "compare"
echo "1000 particles"
echo "50 core checking"
time mpirun -n 50 bin/naive check1000.init
echo "40 core checking"
time mpirun -n 40 bin/naive check1000.init
