#!/bin/sh
#SBATCH -n 8            # 8 CPU cores
#SBATCH -t 0-00:30:00   # 30 minutes
#SBATCH -p debug      # partition name
#SBATCH -J inits     # sensible name for the job



# load up the correct modules, if required
source /etc/profile.d/modules.sh
module load default-gcc-openmpi
make bin/statsNaive

# launch the code
echo "gen"
echo "1000 particles"
time mpirun -n 8 bin/statsNaive compStats/init/gen1000.init
echo "600 particles"
time mpirun -n 8 bin/statsNaive compStats/init/gen600.init
echo "400 particles"
time mpirun -n 8 bin/statsNaive compStats/init/gen400.init
echo "200 particles"
time mpirun -n 8 bin/statsNaive compStats/init/gen200.init
echo "160 particles"
time mpirun -n 8 bin/statsNaive compStats/init/gen160.init
echo "120 particles"
time mpirun -n 8 bin/statsNaive compStats/init/gen120.init
echo "80 particles"
time mpirun -n 8 bin/statsNaive compStats/init/gen80.init
