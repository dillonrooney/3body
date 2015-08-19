#!/bin/sh
#SBATCH -n 8            # 8 CPU cores
#SBATCH -t 0-00:30:00   # 30 minutes
#SBATCH -p debug      # partition name
#SBATCH -J 1000particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/naive

# launch the code
echo "compare"
echo "1000 particles"
echo "2 core checking"
time mpirun -n 2 bin/naive check1000.init
echo "4 core checking"
time mpirun -n 4 bin/naive check1000.init
echo "5 core checking"
time mpirun -n 5 bin/naive check1000.init
echo "8 core checking"
time mpirun -n 8 bin/naive check1000.init
