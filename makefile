CC=gcc
CFLAGS=-Wall --pedantic -std=c99

include src/makefile
include src/simple/makefile
include test/makefile

.PHONY: test clean

default: test

test: src/simple/binary-tree.c src/utils.c test/runner.c
	${CC} ${CFLAGS} ${SRC_FILES} ${TEST_FILES} -o bin/test
	@echo "complete"

clean:
	-@rm ./bin/*
	-@find ./build -name *.o -delete
	@echo "complete"
