#!/bin/sh
#SBATCH -n 16            # 8 CPU cores
#SBATCH -t 0-00:30:00   # 30 minutes
#SBATCH -p debug      # partition name
#SBATCH -J 1024particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi

# launch the code
echo "no gen"
echo "c2"
time mpirun -n 2 bin/naive check1024.ini
echo "c4"
time mpirun -n 4 bin/naive check1024.ini
echo "c16"
time mpirun -n 16 bin/naive check1024.ini
echo "c8"
time mpirun -n 8 bin/naive check1024.ini
