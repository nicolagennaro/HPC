#!/bin/bash

gcc trans_no_blocks.c -o trans_no_blocks -lm

if [ -e times_no_blocks.dat ]; then
    rm times_no_blocks.dat
fi

for matsize in 1024 2048 4096;do
    printf "$matsize\t" >> times_no_blocks.dat
    ./trans_no_blocks $matsize >> times_no_blocks.dat
done
