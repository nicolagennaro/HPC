
set title 'Strong Scaling on a Ulisse Node'
set xlabel 'Proc Number'
set ylabel 'Mean Time (s)'



set terminal png
set output 'strong.png'
plot [-1:21] 'strongplot.dat' u 1:2:3 w yerrorbars title 'mean time',\
     	     		      1.0/x title '1/x'


set title 'Strong Scaling on a Ulisse Node'
set xlabel 'Proc Number'
set ylabel 'Speedup'

set key left top

set terminal png
set output 'speedup.png'
plot [0:21][0:21] 'speedup.dat' u 1:2:3 w yerrorbars title 'speedup', x title 'y=x'




set title 'Weak Scaling on a Ulisse Node'
set xlabel 'Proc Number'
set ylabel 'Mean Time (s)'

set terminal png
set output 'weak.png'
plot [0:21] 'weakplot.dat' u 1:2:3 w yerrorbars title 'times'
