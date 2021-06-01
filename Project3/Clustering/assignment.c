#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structs.h"
#include "functions.h"



void Lloyds_assignment(struct vec *vectors, struct vec *centers, int vec_sum, int coords, int k){
	int i, j;
	double min_dist, dist;
	
	for(i=0; i<vec_sum; i++){
		min_dist = 10000000.0;		
		for(j=0; j<k; j++){
			dist = manhattan_distance(vectors[i], centers[j], coords);
			if(dist  < min_dist ){
				vectors[i].nearest = j;
				min_dist = dist;
			}
		}
		min_dist = 10000000.0;
		for(j=0; j<k; j++){
			dist = manhattan_distance(vectors[i], centers[j], coords);
			if( dist < min_dist && vectors[i].nearest != j){
				vectors[i].second_nearest = j;
				min_dist = dist;
			}
		}
	}
}

void LSH_assignment(struct vec *vectors, struct vec *centers, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int k_clusters, int k, int L){
	int i, j, z, w, quer_sum, m, M, TableSize;
	double range;
	struct vec  *queries;

	w = 4500;
	m = 5;
	M = pow(2, 32/k);
	TableSize = vec_sum/8;

	/**** LSH ***/

	lsh_search(vectors, centers, i, h, HashTables, m_factors, vec_sum, coords, M, k, L, w, TableSize, k_clusters);
}
