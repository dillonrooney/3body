#!/bin/sh
#SBATCH -n 64            # 8 CPU cores
#SBATCH -t 0-00:5:00   # 30 minutes
#SBATCH -p compute      # partition name
#SBATCH -J 1024particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi

# launch the code
echo "nogen"
echo "c64"
time mpirun -n 64 bin/naive check1024.ini
