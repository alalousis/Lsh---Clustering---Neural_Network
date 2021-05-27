#include <stdio.h>
#include "structs.h"

void write_output(char path[256], int quer_sum, struct vec *queries, struct curve *curves, int *lsh_results, int *search_results, int *distanceLSH, int *distanceTrue){
	int i;
	FILE *fp;
	
	fp = fopen(path, "w");
	
	for(i=0; i<quer_sum; i++){
		fprintf(fp, "Query: %d\n", queries[i].id);
		fprintf(fp, "Method: LSH");
		fprintf(fp, "Hash Function: LSH");
		fprintf(fp, "Found Nearest neighbor: %d\n", curves[lsh_results[i]].id);
		fprintf(fp, "True Nearest neighbor: %d\n", curves[search_results[i]].id);
		fprintf(fp, "distanceFound: %d\n", distanceLSH[i]);
		fprintf(fp, "distanceTrue: %d\n", distanceTrue[i]);
	}

}
