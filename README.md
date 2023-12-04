![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/t/AdRi1t/lanzcos?logo=github) ![GitHub top language](https://img.shields.io/github/languages/top/AdRi1t/lanzcos?logo=C&label=Language%20)

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
Three parameters, matrix dimension **n** , subspace **m** and starting $\beta_0 \neq 0 $ value
```
$  ./lanzcos  -n [...]  -m [...]  -b [...]
```
To run the tests, take care to set the value for n to less than 10.
```
$  ./test  -n [...]
```
