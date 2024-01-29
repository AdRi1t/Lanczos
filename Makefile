CC= clang
#CC= icx
OPT= -march=native -O3 -g3
#OPT= -xhost
FLAG= -llapacke -llapack -lblas -Wall -fopenmp -lm
#FLAG= -O3 -g3 -Wall -qopenmp
BUILD_DIR= build
all: buildDir lanczos

buildDir:
	mkdir -p ${BUILD_DIR}

lanczos: ${BUILD_DIR}/main.o ${BUILD_DIR}/matrix.o ${BUILD_DIR}/config.o ${BUILD_DIR}/vector.o ${BUILD_DIR}/operations.o ${BUILD_DIR}/lanczos.o ${BUILD_DIR}/eigen.o ${BUILD_DIR}/mmio.o
	${CC} -o $@ $^ ${FLAG}

test: ${BUILD_DIR}/test.o ${BUILD_DIR}/matrix.o ${BUILD_DIR}/config.o ${BUILD_DIR}/vector.o ${BUILD_DIR}/operations.o ${BUILD_DIR}/lanczos.o ${BUILD_DIR}/eigen.o ${BUILD_DIR}/mmio.o
	${CC} -o $@ $^ ${FLAG}

${BUILD_DIR}/main.o: src/main.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

${BUILD_DIR}/test.o: src/test.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

${BUILD_DIR}/matrix.o: src/matrix.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

${BUILD_DIR}/vector.o: src/vector.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

${BUILD_DIR}/operations.o: src/operations.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

${BUILD_DIR}/lanczos.o: src/lanczos.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

${BUILD_DIR}/eigen.o: src/eigen.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

${BUILD_DIR}/mmio.o: src/mmio.c
	${CC} -c $^ -o $@

${BUILD_DIR}/config.o: src/config.c
	${CC} ${OPT} -c $^ -o $@ ${FLAG}

clean:
	rm -rf build

.PHONY: clean all lanczos

