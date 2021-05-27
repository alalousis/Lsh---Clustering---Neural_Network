#include <stdio.h>
#include "structs.h"

void write_output(char path[256], int quer_sum, struct vec *queries, struct vec *vectors, int *lsh_results, int *distanceLSH, int *distanceTrue, float *tLSH, float *tTrue){
	int i;
	FILE *fp;
	
	fp = fopen(path, "w");
	
	for(i=0; i<quer_sum; i++){
		fprintf(fp, "Query: %d\n", queries[i].id);
		fprintf(fp, "Nearest neighbor: %d\n", vectors[lsh_results[i]].id);
		fprintf(fp, "distanceLSH: %d\n", distanceLSH[i]);
		fprintf(fp, "distanceTrue: %d\n", distanceTrue[i]);
		fprintf(fp, "tLSH:  %f\n", tLSH[i]);
		fprintf(fp, "tTrue: %f\n\n", tTrue[i]);
	}

}
