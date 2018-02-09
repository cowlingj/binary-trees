CC=gcc
CFLAGS=-Wall --pedantic -std=c99

TEST_FILES += \
./test/simple/runner.c

OBJ_FILES += \
./test/simple/runner.o

# Each subdirectory must supply rules for building sources it contributes
# since when something depends on OBJ_FILES make will ask us

# automatic vars
# $< = target
# $@ dependencies

test/simple/%.o: test/simple/%.c
	@echo 'Building file: $<'
	${CC} ${CFLAGS} -o "$@" "$<"
	@mv "$<" build/"$(@D)"/"$@"
	@echo 'Finished building: $<'
	@echo ' '
