OBJS = main.o input.o average.o modulo_calc.o factors.o lsh.o write_output.o cube.o hamming_distance.o
SOURCE = main.c input.c average.c modulo_calc.c factors.c lsh.c write_output.c cube.c hamming_distance.c
HEADER = structs.h functions.h
OUT = cube
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -lm

main.o: main.c
	$(CC) $(FLAG) main.c

input.o: input.c
	$(CC) $(FLAG) input.c

average.o: average.c
	$(CC) $(FLAG) average.c

modulo_calc.o: modulo_calc.c
	$(CC) $(FLAG) modulo_calc.c

factors.o: factors.c
	$(CC) $(FLAG) factors.c

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

write_output.o: write_output.c
	$(CC) $(FLAG) write_output.c

cube.o: cube.c
	$(CC) $(FLAG) cube.c

hamming_distance.o: hamming_distance.c
	$(CC) $(FLAG) hamming_distance.c

clean:
	rm -f $(OBJS) $(OUT)
