#!/bin/sh
#SBATCH -n 8            # 8 CPU cores
#SBATCH -t 0-00:30:00   # 30 minutes
#SBATCH -p debug      # partition name
#SBATCH -J 1536particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/naive

# launch the code
echo "gen"
echo "1536 particles"
echo "4 core checking"
time mpirun -n 4 bin/naive check1536.init
echo "6 core checking"
time mpirun -n 6 bin/naive check1536.init
echo "8 core checking"
time mpirun -n 8 bin/naive check1536.init
