#!/bin/sh
#SBATCH -n 32            # 8 CPU cores
#SBATCH -t 0-00:5:00   # 30 minutes
#SBATCH -p compute      # partition name
#SBATCH -J 768particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/naive

# launch the code
echo "gen"
echo "768 particles"
echo "32 core checking"
time mpirun -n 32 bin/naive check768.init
echo "24 core checking"
time mpirun -n 24 bin/naive check768.init
