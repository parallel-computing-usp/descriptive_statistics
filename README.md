# Descriptive Statistics
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

### Exercise Solutions for the Parallel Computing course at USP
### The goal is to improve a sequential code using functional and data parallelism with OpenMP

## Steps to run
### sequential version
```bash
gcc professor_seq.c -o seq -fopenmp -lm
./professor_seq < matriz_2.txt
```
### parallel version
```bash
gcc openmp_par_func_data.c -o openmp_par_func_data -fopenmp -lm
./openmp_par_func_data < matriz_2.txt
```
