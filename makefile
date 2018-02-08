CC=gcc
CFLAGS=-Wall --pedantic -std=c99

.PHONY: simple clean red-black list

default: list

include src/makefile
include test/makefile
ifeq ($(MAKECMDGOALS),simple)
include src/simple/makefile
include test/simple/makefile
else ifeq ($(MAKECMDGOALS),red-black)
include src/red-black/makefile
include test/red-black/makefile
endif

simple: src/simple/binary-tree.c src/utils.c test/simple/runner.c   
	${CC} ${CFLAGS} ${SRC_FILES} ${TEST_FILES} -o bin/simple
	@echo "complete"

red-black: src/simple/binary-tree.c src/utils.c test/simple/runner.c
	${CC} ${CFLAGS} ${SRC_FILES} ${TEST_FILES} -o bin/red-black
	@echo "complete"

clean:
	-@rm ./bin/*
	-@find ./build -name *.o -delete
	@echo "complete"

list:
	@echo -e "make:"\
"\n\tlist - show available targets"\
"\n\tclean - removes executables and intermedary files"\
"\n\tred-black - builds the tests for a red-black tree"\
"\n\tsimple - builds the tests for a simple (unbalanced binary tree)"
