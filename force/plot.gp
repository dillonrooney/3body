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

set title "10 Particles in a linear configuration"
set output "lin10global.png"
plot "lin10global.dat" 


set title "20 Particles in a random configuration"
set output "random20global.png"
plot "random20global.dat" 


set title "40 Particles in a random configuration"
set output "random40global.png"
plot "random40global.dat" 


set title "3 Particles in a linear configuration"
set output "lin3global.png"
plot "lin3global.dat" 


set title "3 Particles in an equilateral triangle configuration"
set output "equilateralglobal.png"
plot "equilateralglobal.dat" 

f(x) = x*x

set title "Combined accuracy"
set output "combinedglobal.png"
plot "random10global.dat" title '10 random', \
"lin10global.dat" title '10 linear', \
"lin3global.dat" title '3 linear', \
"equilateralglobal.dat" title 'equilateral triangle', \
"random40global.dat" title '40 perturbed grid', \
f(x) title 'h squared', \
"random20global.dat" title '20 perturbed grid'
