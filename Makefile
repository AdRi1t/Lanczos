CC= clang
#CC= icx
OPT= -march=native
#OPT= -xhost
FLAG= -O3 -g3 -Wall -fopenmp -lm
#FLAG= -O3 -Wall -qopenmp
all: lanczos

lanczos: main.o matrix.o config.o vector.o operations.o lanczos.o
	${CC} -o $@ $^ ${FLAG}

test: test.o matrix.o config.o vector.o operations.o lanczos.o
	${CC} -o $@ $^ ${FLAG}

main.o: src/main.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

test.o: src/test.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

matrix.o: src/matrix.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

vector.o: src/vector.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

operations.o: src/operations.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

lanczos.o: src/lanczos.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

config.o: src/config.c
	${CC} -c $^ -o $@ ${FLAG}

clean:
	rm lanczos *.o

