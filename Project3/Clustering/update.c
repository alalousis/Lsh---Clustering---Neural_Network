#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

void PAM(struct vec *vectors, struct vec *centers, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int k, int k_lsh, int L, char vec_asign){
	int i, j, z, min_pos, count, changes, flag;
	double dist, min, min_dist;	

	count = 0;
	changes = 1;
	while(changes != 0 && count < 100){
		changes = 0;
		for(i=0; i<k; i++){					// Update centers
			min = 10000000.0;
			for(j=0; j<vec_sum; j++){
				if(vectors[j].nearest == i){
					dist = 0.0;
					for(z=0; z<vec_sum; z++){
						if(vectors[z].nearest == i){
							dist += manhattan_distance(vectors[j], vectors[z], coords);
						}
					}
					if(dist < min){
						min = dist;
						min_pos = j;
					}
				}
			}
			flag = 0;
			for(j=0; j<coords; j++){
				if(centers[i].coord[j] != vectors[min_pos].coord[j]){
					flag = 1;
					break;
				}
			}
			if(flag){		// Anathetoume to neo kentro
				for(j=0; j<coords; j++){
					centers[i].coord[j] = vectors[min_pos].coord[j];
					
				}
				strcpy(centers[i].id, vectors[min_pos].id);
				changes++;
			}
		}

		if(vec_asign == 1)
			Lloyds_assignment(vectors, centers, vec_sum, coords, k);
		else
			LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L);

		count++;
	}
}


void PAMean(struct vec *vectors, struct vec *centers, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int k, int k_lsh, int L, char vec_asign){
	int i, j, z, min_pos, count, cluster_size, changes, flag;
	double min, min_dist;
	struct vec prev_cent;

	prev_cent.coord = malloc(coords*sizeof(double));

	count = 0;
	changes = 1;
	while(changes != 0 && count < 100){
		changes = 0;
		for(i=0; i<k; i++){					// Update centers
			for(j=0; j<coords; j++)
				prev_cent.coord[j] = centers[i].coord[j];
			for(j=0; j<coords; j++)
				centers[i].coord[j] = 0;
			cluster_size = 0;
			for(j=0; j<vec_sum; j++){
				if(vectors[j].nearest == i){
					cluster_size++;
					for(z=0; z<coords; z++){
						centers[i].coord[z] += vectors[j].coord[z];
					}
				}
			}

			if(cluster_size!=0){
				for(j=0; j<coords; j++)
					centers[i].coord[j] = centers[i].coord[j] / cluster_size;
			}
	
			flag = 0;
			for(j=0; j<coords; j++){
				if(centers[i].coord[j] != prev_cent.coord[j]){
					flag = 1;
					break;
				}
			}
			if(flag)
				changes++;
		}

		if(vec_asign == 1)
			Lloyds_assignment(vectors, centers, vec_sum, coords, k);
		else
			LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L);

		count++;
	}
}
