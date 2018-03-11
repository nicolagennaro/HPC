#!/bin/bash

partnum=2000
griddim=100

echo
echo PARAMETERS:
echo particle number = $partnum
echo grid size = $griddim
echo


echo avoid_avoidable_loop0
./avoid_avoidable_loop0 $partnum $griddim

echo
echo avoid_avoidable_loop1
./avoid_avoidable_loop1 $partnum $griddim

echo
echo avoid_avoidable_loop2
./avoid_avoidable_loop2 $partnum $griddim

echo
echo avoid_avoidable_loop3
./avoid_avoidable_loop3 $partnum $griddim

echo
echo avoid_avoidable_loop4
./avoid_avoidable_loop4 $partnum $griddim

echo
echo avoid_avoidable_loop5
./avoid_avoidable_loop5 $partnum $griddim

echo
echo avoid_avoidable_loop6
./avoid_avoidable_loop6 $partnum $griddim

echo
echo avoid_avoidable_loop7
./avoid_avoidable_loop7 $partnum $griddim

echo
echo avoid_avoidable_loop7b
./avoid_avoidable_loop7b $partnum $griddim

echo
echo avoid_avoidable_loop8
./avoid_avoidable_loop8 $partnum $griddim

echo
echo avoid_avoidable_loop8b
./avoid_avoidable_loop8b $partnum $griddim

echo
echo avoid_avoidable_loop8pref
./avoid_avoidable_loop8pref $partnum $griddim

