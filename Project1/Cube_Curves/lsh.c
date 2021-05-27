#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

void lsh_train(struct vec *vectors, struct h_func *h, int *m_factors, int **h_sum, int vec_sum, int coords, int M, int d, int w){
	int i, j, z, hash_pos, *a;
	float f;

	a = malloc(coords*sizeof(int));
	for(i=0; i<vec_sum; i++){
		for(z=0; z<d; z++){						
			h[z].h_sum = 0;
			for(j=0; j<coords; j++){	
				f = (float) (vectors[i].coord[j] - h[z].s[j]) / w;			//Briskoume kathe a[j]
				a[j] = floor(f) + 2;						//Efarmozoume to floor kai ta kanoume thetika
				h[z].h_sum += (a[j] % M * m_factors[j]) % M; 				//Kanoume mod se kathe paragonta kai athroizoume
			}
			h[z].h_sum = h[z].h_sum % M;			//Kanoume mod kai so oloklhro to athroisma
			h_sum[i][z] = h[z].h_sum;
		}
	}
}

void lsh_search(struct vec query, struct h_func *h, int *m_factors, int *h_quer, int coords, int M, int d, int w){
	int i, j, *a;
	float f;

	a = malloc(coords*sizeof(int));
	for(i=0; i<d; i++){			// Efarmozoume tin idia diadikasia gia to query							
		h[i].h_sum = 0;
		for(j=0; j<coords; j++){
			f = (float) (query.coord[j] - h[i].s[j]) / w;
			a[j]=floor(f) + 2;
			h[i].h_sum += (a[j] % M * m_factors[j]) % M;
		}
		h[i].h_sum = h[i].h_sum % M;
		h_quer[i] = h[i].h_sum;
	}
}
