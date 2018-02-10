CC=gcc
CFLAGS=-Wall --pedantic -g -std=c99

TEST_FILES += \
./test/red-black/runner.c

OBJ_FILES += \
./test/red-black/runner.o

# Each subdirectory must supply rules for building sources it contributes
# since when something depends on OBJ_FILES make will ask us

# automatic vars
# $< = target
# $@ dependencies

test/red-black/%.o: test/red-black/%.c
	@echo 'Building file: $<'
	${CC} ${CFLAGS} -o "$@" "$<"
	@mv "$<" build/"$(@D)"/"$@"
	@echo 'Finished building: $<'
	@echo ' '
