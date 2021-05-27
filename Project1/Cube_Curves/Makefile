OBJS = main.o input.o euclidean.o dtw.o count_d.o snap.o concat_curve.o search.o factors.o lsh.o modulo_calc.o cube.o hamming_distance.o
SOURCE = main.c input.c euclidean.c dtw.c count_d.c snap.c concat_curve.c search.c factors.c lsh.c modulo_calc.c cube.c hamming_distance.c
HEADER = headers.h functions.h
OUT = curve_grid_hypercube
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -lm

main.o: main.c
	$(CC) $(FLAG) main.c

input.o: input.c
	$(CC) $(FLAG) input.c

euclidean.o: euclidean.c
	$(CC) $(FLAG) euclidean.c

dtw.o: dtw.c
	$(CC) $(FLAG) dtw.c

count_d.o: count_d.c
	$(CC) $(FLAG) count_d.c

snap.o: snap.c
	$(CC) $(FLAG) snap.c

concat_curve.o: concat_curve.c
	$(CC) $(FLAG) concat_curve.c


search.o: search.c
	$(CC) $(FLAG) search.c

modulo_calc.o: modulo_calc.c
	$(CC) $(FLAG) modulo_calc.c

factors.o: factors.c
	$(CC) $(FLAG) factors.c

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

cube.o: cube.c
	$(CC) $(FLAG) cube.c

hamming_distance.o: hamming_distance.c
	$(CC) $(FLAG) hamming_distance.c

clean:
	rm -f $(OBJS) $(OUT)
