#!/bin/bash

# function to get timestamp
timestamp() {
  date +"%Y%m%d-%H:%M:%S"
}

# create results directory
mkdir -p results

# parameters
matrix_size=1024
number_iterations=50

# dgemm_0

algorithm=0

while [ $algorithm -le 2 ]
do
  printf "Making tests with dgemm_$algorithm...\n"

  file="results/$(timestamp)-$algorithm-$matrix_size-$number_iterations.txt"
  echo "implementation;n;time" >> $file

  i=1
  
  while [ $i -le $number_iterations ]
  do
    ./main --matrix-size $matrix_size --algorithm 0 >> $file
    (( i += 1 ))
  done
  (( algorithm += 1 ))
done
