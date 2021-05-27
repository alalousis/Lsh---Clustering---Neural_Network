#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, k, L, w, vec_sum, quer_sum, coords, m, M, *m_factors, TableSize, *search_results, *lsh_results, *distanceTrue, *distanceLSH;
	char ch, *num, input[256], query[256], output[256];
	float r, *tLSH, *tTrue;
	clock_t start, stop;
	struct vec *vectors, *queries;
	FILE *fp;	

	if(argc==11){					// Pairnoume ta orismata
		strcpy(input, argv[2]);
		strcpy(query, argv[4]);
		k = atoi(argv[6]);
		L = atoi(argv[8]);
		strcpy(output, argv[10]);
	
	}else{							// An den itan arketa diavazoume ta files ap to pliktrologio
		k = 4;
		L = 5;								
		printf("k = 4\tL = 5\nGive the path to the input file:\n");
		scanf("%s", input);
		printf("Give the path to the query file:\n");
		scanf("%s", query);
		printf("Give the path to the output file:\n");
		scanf("%s", output);
		strcpy(output, "output");
	}

	count_input(input, &vec_sum, &coords);						// Metrame to plithos twn dianusmatwn
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(int));
	}
	save_input(input, vectors);									// Apothikeuoume ta dianusmata

	count_input(query, &quer_sum, &coords);						// Metrame to plithos twn queries
	queries = malloc(quer_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume
	for(i=0; i<quer_sum; i++){
		queries[i].coord = malloc(coords*sizeof(int));
	}
	save_input(query, queries);						// Apothikeuoume ta queries

	search_results = malloc(quer_sum*sizeof(int));
	lsh_results = malloc(quer_sum*sizeof(int));
	distanceTrue = malloc(quer_sum*sizeof(int));
	distanceLSH = malloc(quer_sum*sizeof(int));
	tLSH = malloc(quer_sum*sizeof(float));
	tTrue = malloc(quer_sum*sizeof(float));

	for(i=0; i<quer_sum; i++){
		start = clock();
		search_results[i] = query_knn(vec_sum, coords, vectors, queries[i], &distanceTrue[i]);	// Kwdikas exantlitikis anazitisis
		stop = clock();
		tTrue[i] = (double)(stop-start) / CLOCKS_PER_SEC;
	}

//	r = average_dist(vec_sum, coords, vectors);			// Kwdikas gia ton upologismo tou r wste na thesoume w = 4*r
	w = 4500;

	lsh(vectors, queries, vec_sum, quer_sum, coords, k, L, w, lsh_results, distanceLSH, tLSH);
	write_output(output, quer_sum, queries, vectors, lsh_results, distanceLSH, distanceTrue, tLSH, tTrue);

	return 0;
}
