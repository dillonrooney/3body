#!/bin/sh
#SBATCH -n 64            # 8 CPU cores
#SBATCH -t 0-00:10:00   # 30 minutes
#SBATCH -p compute      # partition name
#SBATCH -J 1536particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/naive

# launch the code
echo "gen"
echo "1536 particles"
echo "48 core checking"
time mpirun -n 48 bin/naive check1536.init
echo "64 core checking"
time mpirun -n 64 bin/naive check1536.init