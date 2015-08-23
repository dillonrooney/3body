#!/bin/sh
#SBATCH -n 1            # 1 CPU cores
#SBATCH -t 0-00:30:00   # 30 minutes
#SBATCH -p debug      # partition name
#SBATCH -J histogram     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/statsNaive

# launch the code
echo "comp"
echo "1000 particles"
time mpirun -n 1 bin/statsNaive compStatsInit/comp1000.init
echo "160 particles"
time mpirun -n 1 bin/statsNaive compStatsInit/comp160.init
echo "120 particles"
time mpirun -n 1 bin/statsNaive compStatsInit/comp120.init
echo "80 particles"
time mpirun -n 1 bin/statsNaive compStatsInit/comp10.init
