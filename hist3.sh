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
echo "600 particles"
time mpirun -n 1 bin/statsNaive compStats/init/comp600.init
echo "400 particles"
time mpirun -n 1 bin/statsNaive compStats/init/comp400.init
echo "200 particles"
time mpirun -n 1 bin/statsNaive compStats/init/comp200.init
