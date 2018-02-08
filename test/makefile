CC=gcc
CFLAGS=-Wall --pedantic -std=c99

TEST_FILES += \
./test/runner.c

OBJ_FILES += \
./test/runner.o

# Each subdirectory must supply rules for building sources it contributes
# since when something depends on OBJ_FILES make will ask us

# automatic vars
# $< = target
# $@ dependencies

test/%.o: test/%.c
	@echo 'Building file: $<'
	${CC} ${CFLAGS} -o "$@" "$<"
	@mv "$<" build/"$(@D)"/"$@"
	@echo 'Finished building: $<'
	@echo ' '