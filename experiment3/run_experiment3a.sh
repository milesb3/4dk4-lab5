#!/bin/bash

#Define values to sweep
declare -a B_T_MAX_vals=("1" "2" "3" "5" "7" "10")
declare -a B_D_MAX_vals=($(seq 1 1 10))

for B_T_MAX in "${B_T_MAX_vals[@]}"
do
    for B_D_MAX in "${B_D_MAX_vals[@]}"
    do
        #Update values of B_T_MAX and B_D_MAX for this simulation run
        sed -i "s/#define B_T_MAX.*/#define B_T_MAX ${B_T_MAX}/" simparameters.h
        sed -i "s/#define B_D_MAX.*/#define B_D_MAX ${B_D_MAX}/" simparameters.h

        #Update output csv filename
        sed -i "s/OUTPUT_CSV_FILE.*/OUTPUT_CSV_FILE \"results\/experiment3a-${B_T_MAX}-${B_D_MAX}.csv\"/" simparameters.h

        #Recompile and run simulation
        make
        ./lab5_experiment3a
    done
done
