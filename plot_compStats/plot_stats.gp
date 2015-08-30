set term png

set xlabel "Relative Difference (eps)"
set ylabel "Probability Density"

set title "Probability Density of Relative Difference"
set output "reldiff_hist.png"

set xrange [0:300]

plot "1000" using  1:2 with lines title "1000 particles", "600" using  1:2 with lines title "600 particles", "400" using  1:2 with lines title "400 particles", "200" using  1:2 with lines title "200 particles", "160" using  1:2 with lines title "160 particles", "120" using  1:2 with lines title "120 particles", "80" using  1:2 with lines title "80 particles"

unset xrange

set output "reldiff_mean.png"

set title "Mean of Relative Difference"
set xlabel "Number of Particles"
set ylabel "Mean Relative Difference (eps)"
plot 'means' using 1:2
#:3 with yerrorbars

