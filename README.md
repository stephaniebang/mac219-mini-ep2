# Mini EP 2

## Test battery
To execute a test battery, first give the shell script tests.sh permission to execute with the command
```
chmod 755 tests.sh
```
and then run the script with the command
```
./tests.sh
```
The files with the resulting data will be saved in the directory ./results.

## Test analysis
To run a test analysis, run the R script with the command
```
Rscript resultsAnalysis.R
```
It is important to notice that the scripts made are very simple and the R script only analyzes the 3 first files in the ./results directory
