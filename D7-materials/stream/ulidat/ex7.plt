set title "Stream Benchmark on a Ulisse's Node"
set xlabel 'Number of Threads'
set ylabel 'Bandwidth (MB/s)'

set key right bottom

set terminal png
set output 'bandwidth.png'
plot [0:11] 'filethreads00.dat' u 1:2 w lp title 'Same Node',\
     	     'filethreads01.dat' u 1:2 w lp title 'Different Node'