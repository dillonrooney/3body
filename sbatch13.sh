#!/bin/sh
#SBATCH -n 32            # 8 CPU cores
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
echo "20 core checking"
time mpirun -n 20 bin/naive check1000.init
echo "25 core checking"
time mpirun -n 25 bin/naive check1000.init
