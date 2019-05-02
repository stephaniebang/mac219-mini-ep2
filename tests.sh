#!/bin/bash

# function to get timestamp
timestamp() {
  date +"%Y%m%d-%H:%M:%S"
}

# create results directory
mkdir -p results

# compile program
make

# parameters
matrix_size=2048
number_iterations=40

algorithm=0

while [ $algorithm -le 2 ]
do
  printf "Making tests with dgemm_$algorithm...\n"

  file="results/$(timestamp)-$algorithm-$matrix_size-$number_iterations.txt"
  echo "n;time(s)" >> $file

  i=1
  
  while [ $i -le $number_iterations ]
  do
    ./main --matrix-size $matrix_size --algorithm $algorithm >> $file
    (( i += 1 ))
  done
  (( algorithm += 1 ))
done
