#!/bin/sh
#SBATCH -n 8            # 8 CPU cores
#SBATCH -t 0-00:30:00   # 30 minutes
#SBATCH -p debug      # partition name
#SBATCH -J timing_test     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi

# launch the code

time mpirun -n 2 bin/naive time1000.ini
time mpirun -n 4 bin/naive time1000.ini
time mpirun -n 5 bin/naive time1000.ini
time mpirun -n 8 bin/naive time1000.ini
