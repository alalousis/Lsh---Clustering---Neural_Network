#include <stdio.h>
#include "structs.h"

void write_output(char path[256], int quer_sum, struct vec *queries, struct vec *vectors, int *cube_results, int *distanceCube, int *distanceTrue, float *tCube, float *tTrue){
	int i;
	FILE *fp;
	
	fp = fopen(path, "w");
	
	for(i=0; i<quer_sum; i++){
		fprintf(fp, "Query: %d\n", queries[i].id);
		fprintf(fp, "Nearest neighbor: %d\n", vectors[cube_results[i]].id);
		fprintf(fp, "distanceCube: %d\n", distanceCube[i]);
		fprintf(fp, "distanceTrue: %d\n", distanceTrue[i]);
		fprintf(fp, "tCube:  %f\n", tCube[i]);
		fprintf(fp, "tTrue: %f\n\n", tTrue[i]);
	}

}
