set term png

set xlabel "stepsize h"
set ylabel "Energy Difference"

set logscale x
set logscale y
set format x '%2g'
set format y '%2g'

set title "3 Particles in a linear configuration, 1 leapfrog step"
set output "lin3local1.png"
plot "lin3local1.dat" 

set title "3 Particles in a linear configuration, 10 leapfrog steps"
set output "lin3local10.png"
plot "lin3local10.dat" 

set title "10 Particles in a linear configuration, 1 leapfrog step"
set output "lin10local1.png"
plot "lin3local1.dat" 

set title "10 Particles in a linear configuration, 10 leapfrog steps"
set output "lin10local10.png"
plot "lin10local10.dat" 
