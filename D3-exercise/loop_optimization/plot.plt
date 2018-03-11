
set title 'Loop optimization'
set xlabel 'Loop type'
set ylabel 'Mean Time (s)'

# unset key


set terminal png
set output 'loops.png'
# with lines points
plot 'loop-1000-100.dat' u 2:xticlabels(1) w lp title '1000-100',\
     'loop-2000-100.dat'  u 2:xticlabels(1) w lp title '2000-100',\
     'loop-2000-50.dat'  u 2:xticlabels(1) w lp title '2000-50',\
     'loop-1000-50.dat' u 2:xticlabels(1) w lp title '1000-50'
# to use the first column as string under the x axis
# plot 'looptimes.dat' u 2:xticlabels(1) w lp
