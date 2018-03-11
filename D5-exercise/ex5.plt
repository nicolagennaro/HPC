set title 'Times for block-transpose algorithm on my laptop'
set xlabel 'Block Size'
set ylabel 'Mean Time (s)'


set key right bottom
set logscale
# unset logscale x

set terminal png
set output 'times_laptop.png'
plot 'time_trans1024.dat' u 1:2:3 w yerrorbars notitle, '' u 1:2 w l title '1024', 0.02194 title '1024 no blocks',\
     'time_trans2048.dat' u 1:2:3 w yerrorbars notitle, '' u 1:2 w l title '2048', 0.08992 title '2048 no blocks',\
     'time_trans4096.dat' u 1:2:3 w yerrorbars notitle, '' u 1:2 w l title '4096', 0.37006 title '4096 no blocks'


set title 'L1 cache misses for block-transpose algorithm on my laptop'
set xlabel 'Block Size'
set ylabel 'L1 cache misses'


set terminal png
set output 'cache_laptop.png'
plot 'cache_trans1024.dat' u 1:2 w lp title '1024',\
     'cache_trans2048.dat' u 1:2 w lp title '2048',\
     'cache_trans4096.dat' u 1:2 w lp title '4096',\