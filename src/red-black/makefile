CC=gcc
CFLAGS=-Wall --pedantic -std=c99

SRC_FILES += \
./src/red-black/binary-tree.c

OBJ_FILES += \
./src/red-black/binary-tree.o

# Each subdirectory must supply rules for building sources it contributes
# since when something depends on OBJ_FILES make will ask us

# automatic vars
# $< = first prerequisite
# $@ = target

src/red-black/%.o: src/red-black/%.c
	@echo 'Building file: $<'
	${CC} ${CFLAGS} -o "$@" "$<"
	@mv "$<" build/"$(@D)"/"$@"
	@echo 'Finished building: $<'
	@echo ' '
