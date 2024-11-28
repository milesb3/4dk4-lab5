#!/bin/bash

#Define variables
outfile="experiment3a_all.csv"
data_folder="results"

#Initialize outfile
echo "random seed, packet arrival rate, T, B_T_MAX, B_D_MAX, packet arrival count, number of packets lost, number of packets transmitted, packet loss rate, average output data rate" > $outfile

#Loop through simulation output files
for filename in ${data_folder}/*.csv
do
    grep -v "random seed," $filename >> $outfile
done