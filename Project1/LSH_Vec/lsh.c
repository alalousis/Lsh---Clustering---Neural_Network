#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "structs.h"
#include "functions.h"

void lsh_train(struct vec *vectors, struct h_func **h, struct list_node ***HashTables, int *m_factors, int vec_sum, int coords, int M, int k, int L, int w, int TableSize){
	int i, j, z, t, hash_pos, *a;
	unsigned int g;
	float f;

	a = malloc(coords*sizeof(int));
	for(i=0; i<vec_sum; i++){
		for(z=0; z<L; z++){
			for(t=0; t<k; t++){								
				h[z][t].h_sum = 0;
				for(j=0; j<coords; j++){
					f = (float) (vectors[i].coord[j] - h[z][t].s[j]) / w;			//Briskoume kathe a[j]
					a[j]=floor(f) + 2;						//Efarmozoume to floor kai ta kanoume thetika
					h[z][t].h_sum += (a[j] % M * m_factors[j]) % M; 				//Kanoume mod se kathe paragonta kai athroizoume
				}
				h[z][t].h_sum = h[z][t].h_sum % M;			//Kanoume mod kai so oloklhro to athroisma
			}
			g = concat(h[z], k);
			hash_pos = g % (TableSize);
			hash(HashTables[z], hash_pos, g, i);
		}
	}
}

int lsh_search(struct vec *vectors, struct vec query, struct h_func **h, struct list_node ***HashTables, int *m_factors, int *min_distance, int vec_sum, int coords, int M, int k, int L, int w, int TableSize){
	int i, j, z, t, hash_pos, *a, min, min_pos, vec_pos, dist;
	unsigned int g;
	float f;
	struct list_node *cur;


	a = malloc(coords*sizeof(int));
	min=10000000;
	min_pos=-1;
	for(z=0; z<L; z++){			// Efarmozoume tin idia diadikasia gia to query
		for(t=0; t<k; t++){								
			h[z][t].h_sum = 0;
			for(j=0; j<coords; j++){
				f = (float) (query.coord[j] - h[z][t].s[j]) / w;
				a[j]=floor(f) + 2;
				h[z][t].h_sum += (a[j] % M * m_factors[j]) % M;
			}
			h[z][t].h_sum = h[z][t].h_sum % M;
		}
		g = concat(h[z], k);
		hash_pos = g % (TableSize);			// Molis antistoixithei se bucket
		if(HashTables[z][hash_pos]!=NULL){	// An to bucket den einai adeio
			cur=HashTables[z][hash_pos];
			while(cur!=NULL){				// Trexoume olo to bucket
				if(cur->g==g){				// Kai an ta dianusmata tou bucket exoun idio g me to query
					vec_pos=cur->vec_pos;
					dist=0;					// Metrame tin manhattan distance
					for(j=0; j<coords; j++){
						dist+=abs(vectors[vec_pos].coord[j]-query.coord[j]);
					}
					if(dist<min){			// Apothikeuoume to mikrotero
						min_pos=vec_pos;
						min=dist;
					}
					dist=0;
				}
				cur=cur->next;
			}
		}
		
	}
	*min_distance=min;
	return min_pos;							// Ki epistrefoume tin thesi tou ston pinaka vectors
}

void lsh(struct vec *vectors, struct vec *queries, int vec_sum, int quer_sum, int coords, int k, int L, int w, int *lsh_results, int *distanceLSH, float *tLSH){
	int i, j, z, m, M, hash_pos, TableSize, *m_factors;
	struct h_func **h; 
	struct list_node ***HashTables;
	clock_t start, stop;

	h = malloc(L*sizeof(struct h_func *));			// Ftiaxnoume tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<L; i++){	
		h[i] = malloc(k*sizeof(struct h_func));
	}
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			h[i][j].s = malloc(coords*sizeof(int));
		}
	}

	srand(time(0));												// Dinoume tuxaies times sta s sto diastima [0,w)
	for(i=0; i<L; i++){
		for(j=0; j<k; j++){
			for(z=0; z<coords; z++){
				h[i][j].s[z] = w*(rand() / (RAND_MAX +1.0));
			}
		}
	}
	
	TableSize = vec_sum/8;										// Kanoume malloc gia tous L Hashtables
	HashTables = malloc(L*sizeof(struct list_node **));
	for(i=0; i<L; i++){
		HashTables[i] = malloc(TableSize*sizeof(struct list_node *));
	}
	for(i=0; i<L; i++){											// Ola ta buckets twn hashtables dixnoun NULL
		for(j=0; j<TableSize; j++){
			HashTables[i][j] = NULL;
		}
	}

	m = 5;												// Ekxwroume times sta m, M
	M = pow(2, 32/k);

	m_factors = malloc(coords*sizeof(int));						// Apothikeuoume ola ta (m^d) mod M, gia na min kanoume askopous upologismous
	factors(m, M, coords, m_factors);

	lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k, L, w, TableSize);		// Ekteloume to lsh gia to input data

	for(i=0; i<quer_sum; i++){									// Ekteloume lsh gia ta queries
		start = clock();
		lsh_results[i] = lsh_search(vectors, queries[i], h, HashTables, m_factors, &distanceLSH[i], vec_sum, coords, M, k, L, w, TableSize);
		stop = clock();
		tLSH[i] = (double)(stop-start) / CLOCKS_PER_SEC;
	}
}
