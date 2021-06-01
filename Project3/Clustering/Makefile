OBJS = main.o input.o manhattan_distance.o initialization.o assignment.o update.o lsh.o lsh_functions.o silhouette.o write_output.o
SOURCE = main.c input.c manhattan_distance.c initialization.c assignment.c update.c lsh.c lsh_functions.c silhouette.c write_output.c
HEADER = structs.h functions.h 
OUT = cluster
CC = gcc
FLAG = -c 

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -lm

main.o: main.c
	$(CC) $(FLAG) main.c

input.o: input.c
	$(CC) $(FLAG) input.c

manhattan_distance.o: manhattan_distance.c
	$(CC) $(FLAG) manhattan_distance.c

initialization.o: initialization.c
	$(CC) $(FLAG) initialization.c

assignment.o: assignment.c
	$(CC) $(FLAG) assignment.c

update.o: update.c
	$(CC) $(FLAG) update.c

lsh.o: lsh.c
	$(CC) $(FLAG) lsh.c

lsh_functions.o: lsh_functions.c
	$(CC) $(FLAG) lsh_functions.c

silhouette.o: silhouette.c
	$(CC) $(FLAG) silhouette.c

write_output.o: write_output.c
	$(CC) $(FLAG) write_output.c

clean:
	rm -f $(OBJS) $(OUT)
