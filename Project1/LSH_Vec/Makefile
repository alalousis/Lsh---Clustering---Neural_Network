OBJS = main.o input.o average.o modulo_calc.o concat.o factors.o hash.o lsh.o write_output.o
SOURCE = main.c input.c average.c modulo_calc.c concat.c factors.c hash.c lsh.c write_output.c
HEADER = structs.h functions.h
OUT = lsh
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

concat.o: concat.c
	$(CC) $(FLAG) concat.c

factors.o: factors.c
	$(CC) $(FLAG) factors.c

hash.o: hash.c
	$(CC) $(FLAG) hash.c

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

write_output.o: write_output.c
	$(CC) $(FLAG) write_output.c

clean:
	rm -f $(OBJS) $(OUT)
