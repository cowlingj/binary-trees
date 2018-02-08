CC=gcc
CFLAGS=-Wall --pedantic -std=c99

SRC_FILES += \
./src/utils.c

OBJ_FILES += \
./src/utils.o

# Each subdirectory must supply rules for building sources it contributes
# since when something depends on OBJ_FILES make will ask us

# automatic vars
# $< = target
# $@ dependencies

src/%.o: src/%.c
	@echo 'Building file: $<'
	${CC} ${CFLAGS} -o "$@" "$<"
	@mv "$<" build/"$(@D)"/"$@"
	@echo 'Finished building: $<'
	@echo ' '