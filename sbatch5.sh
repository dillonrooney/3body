#!/bin/sh
#SBATCH -n 32            # 8 CPU cores
#SBATCH -t 0-00:5:00   # 30 minutes
#SBATCH -p compute      # partition name
#SBATCH -J 1024particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi

# launch the code
echo "nogen"
echo "c32"
time mpirun -n 32 bin/naive check1024.ini
