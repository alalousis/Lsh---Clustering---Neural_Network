#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include <math.h>
#include "functions.h"

void cube_train(int **h_sum, struct list_node ***f, struct list_node **cube, int vec_sum, int d){
	int i, j, hash_pos, cube_pos;
	struct list_node *cur;

	srand(time(0));
	for(i=0; i<vec_sum; i++){
		cube_pos = 0;
		for(j=0; j<d; j++){
			hash_pos = h_sum[i][j] % 4999;
			if(f[j][hash_pos ] == NULL){
				f[j][hash_pos] = malloc(sizeof(struct list_node));
				f[j][hash_pos]->next = NULL;
				f[j][hash_pos]->g = h_sum[i][j];
				f[j][hash_pos]->vec_pos = 2*(rand() / (RAND_MAX +1.0));
				cube_pos += f[j][hash_pos]->vec_pos*pow(2,d-1 -j);		// Den apothikeuoume to diadiko string alla to xrisimopoume gia na broume se poia korifi tou kubou tha paei to dianusma
			}else{
				cur = f[j][hash_pos];
				while(cur->next!=NULL && cur->g!=h_sum[i][j]){
					cur = cur->next;
				}
				if(cur->g != h_sum[i][j]){
					cur->next = malloc(sizeof(struct list_node));
					cur->next->g = h_sum[i][j];
					cur->next->next = NULL;
					cur->next->vec_pos = 2*(rand() / (RAND_MAX +1.0));
				}
				cube_pos += cur->vec_pos*pow(2,d-1 -j);
			}
		}
		if(cube[cube_pos] == NULL){
			cube[cube_pos] = malloc(sizeof(struct list_node));
			cube[cube_pos]->next = NULL;
			cube[cube_pos]->vec_pos = i;
		}else{
			cur = cube[cube_pos];
			while(cur->next!=NULL){
				cur = cur->next;
			}
			cur->next = malloc(sizeof(struct list_node));
			cur->next->next = NULL;
			cur->next->vec_pos = i;
		}
	}
}

int cube_search(int *h_quer, struct list_node ***f, struct list_node **cube, struct vec *vectors, struct vec query, int *distanceCube, int vec_sum, int coords, int d, int probes, int M){
	int i, j, hash_pos, vec_pos, min, min_pos, dist, *cube_pos, *binary_string, count;
	struct list_node *cur;

	binary_string = malloc(d*sizeof(int));
	cube_pos = malloc(probes*sizeof(int));

	srand(time(0));
	for(j=0; j<d; j++){
		hash_pos = h_quer[j] % 4999;
		if(f[j][hash_pos] == NULL){
			binary_string[j] = 2*(rand() / (RAND_MAX +1.0));
		}else{
			cur = f[j][hash_pos];
			while(cur->next!=NULL && cur->g!=h_quer[j]){
				cur = cur->next;
			}
			if(cur->g != h_quer[j]){
				binary_string[j] = 2*(rand() / (RAND_MAX +1.0));
			}else{
				binary_string[j] = cur->vec_pos;
			}
		}
	}
	min = 1000000;
	min_pos = -1;
	i=0;
	edges(binary_string, cube_pos, probes, d);

	for(i=0; i<probes; i++){
		if(cube[cube_pos[i]] != NULL){
			count=0;
			cur = cube[cube_pos[i]];
			while(cur!=NULL && count<M){
				vec_pos = cur->vec_pos;
				dist=0;					// Metrame tin manhattan distance
				for(j=0; j<coords; j++){
					dist+=abs(vectors[vec_pos].coord[j]-query.coord[j]);
				}
				if(dist<min){			// Apothikeuoume to mikrotero
					min_pos=vec_pos;
					min=dist;
				}
				cur = cur->next;
//				count++;			To afinoume sxoliasmeno, wste na min exei kritirio termatismou	
			}
		}
	}
	*distanceCube = min;
	return min_pos;
}
