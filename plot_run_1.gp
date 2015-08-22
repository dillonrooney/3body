set term png

set xlabel "cores"
set ylabel "1/time taken"

set title "Naive algorithm speed"
set output "plot_r1/naive.png"

plot "plot_r1/r1_1000_naive.dat" using ($4):(1/$5) title "1000 particles", "plot_r1/r1_768_naive.dat" using ($4):(1/$5) title "768 particles", "plot_r1/r1_1536_naive.dat" using ($4):(1/$5) title "1536 particles"

set logscale x
set logscale y


set output "plot_r1/naive_loglog.png"
replot

unset logscale x
unset logscale y

set title "Writing speed"
set output "plot_r1/writing.png"

plot "plot_r1/r1_1000_writing.dat" using ($4):(1/$5) title "1000 particles", "plot_r1/r1_768_writing.dat" using ($4):(1/$5) title "768 particles", "plot_r1/r1_1536_writing.dat" using ($4):(1/$5) title "1536 particles"

set logscale x
set logscale y


set output "plot_r1/writing_loglog.png"
replot

unset logscale x
unset logscale y

set title "reading time"
set output "plot_r1/reading_time.png"
set ylabel "time taken"

plot "plot_r1/r1_1000_init_read.dat" using ($4):($5) title "1000 particles", "plot_r1/r1_768_init_read.dat" using ($4):($5) title "768 particles", "plot_r1/r1_1536_init_read.dat" using ($4):($5) title "1536 particles"

set title "reading speed"
set output "plot_r1/reading.png"
set ylabel "1/time taken"

plot "plot_r1/r1_1000_init_read.dat" using ($4):(1/$5) title "1000 particles", "plot_r1/r1_768_init_read.dat" using ($4):(1/$5) title "768 particles", "plot_r1/r1_1536_init_read.dat" using ($4):(1/$5) title "1536 particles"

set logscale x
set logscale y


set output "plot_r1/reading_loglog.png"
replot

unset logscale x
unset logscale y

set title "Data Generation speed"
set output "plot_r1/data_generation.png"

plot "plot_r1/r1_1000_init_gen2.dat" using ($4):(1/$5) title "1000 particles", "plot_r1/r1_768_init_gen2.dat" using ($4):(1/$5) title "768 particles", "plot_r1/r1_1536_init_gen2.dat" using ($4):(1/$5) title "1536 particles"

set logscale x
set logscale y


set output "plot_r1/data_generation_loglog.png"
replot

unset logscale x
unset logscale y

set title "Comparison Time"
set output "plot_r1/comparison_time.png"
set ylabel "time taken"

plot "plot_r1/r1_1000_comparison.dat" using ($4):($5) title "1000 particles", "plot_r1/r1_768_comparison.dat" using ($4):($5) title "768 particles", "plot_r1/r1_1536_comparison.dat" using ($4):($5) title "1536 particles"



set title "Comparison speed"
set output "plot_r1/comparison.png"
set ylabel "1/time taken"

plot "plot_r1/r1_1000_comparison.dat" using ($4):(1/$5) title "1000 particles", "plot_r1/r1_768_comparison.dat" using ($4):(1/$5) title "768 particles", "plot_r1/r1_1536_comparison.dat" using ($4):(1/$5) title "1536 particles"





