![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/t/AdRi1t/Lanczos?logo=github) ![GitHub top language](https://img.shields.io/github/languages/top/AdRi1t/Lanczos?logo=C&label=Language%20)

## Lanczos algorithm for Hermitian matrices
Algorithm description : [Wikipedia](https://en.wikipedia.org/wiki/Lanczos_algorithm)

### How to compile

- Change the comments in the Makefile according to the compiler you want.
```
$ make
```
- Build the executable for testing.
```
$ make test
```

### How to run it
Three parameters, matrix dimension **n** , subspace **m** and starting $\beta_0 \neq 0$ value
```
$  ./lanczos  -n [...]  -m [...]  -b [...]
```
To run the tests, take care to set the value for n to less than 10.
```
$  ./test  -n [...]
```
To run the benchmark add -B<arg>.
```
$  ./lanczos  -n [...]  -m [...]  -b [...] -B [benchmark number]
```
- 1 : Parallel benchmark for fixed matrix size and fixed m with a number of threads ranging from 1 to 40.
- 2 : Sequential benchmark for a fixed matrix size and m ranges from 5 to 50
 
### Plot the result
You can plot the results of multiple runs
- To obtain the graph of a sequential execution with m varying from 5 to 50.
```
$  cd result
$  python3 plot_m.py [file_1.txt] [file_2.txt] ...
```
- To obtain the graph of a parallel execution with a number of threads from 1 to 40
```
$  cd result
$  python3 plot_speedup.py [file_1.txt] [file_2.txt] ...
```
