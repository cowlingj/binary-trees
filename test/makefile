CC=gcc
CFLAGS=-Wall --pedantic -g -std=c99

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
