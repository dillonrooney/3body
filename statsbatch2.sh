#!/bin/sh
#SBATCH -n 8            # 8 CPU cores
#SBATCH -t 0-00:30:00   # 30 minutes
#SBATCH -p debug      # partition name
#SBATCH -J 1536particles     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/statsNaive

# launch the code
echo "gen"
echo "1536 particles"
echo "printing comparison standard deviation:4 processes"
time mpirun -n 4 bin/statsNaive compStats1536.init
echo "printing comparison standard deviation:6 processes"
time mpirun -n 6 bin/statsNaive compStats1536.init
echo "printing comparison standard deviation:8 processes"
time mpirun -n 8 bin/statsNaive compStats1536.init
