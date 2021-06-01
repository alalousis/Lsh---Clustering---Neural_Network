#include <time.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

void random_selection(struct vec *vectors, int vec_sum, int k){
	int i, c;

	srand(time(0));							
	for(i=0; i<k; i++){
		do{							//Etsi wste na mh einai hdh medoid
			c = vec_sum*(rand() / (RAND_MAX +1.0));
		}
		while(vectors[c].isMedoid == 1);
		vectors[c].isMedoid = 1;
	}
}

void k_means_plus_plus(struct vec *vectors, int vec_sum, int k, int coords){
	int i, j, c, centers_count, *centers;
	double *P, *D, dist, max, random;

	D = malloc((vec_sum-1)*sizeof(double));
	P = malloc((vec_sum-1)*sizeof(double));
	centers = malloc(k*sizeof(int));

	srand(time(0));							
	centers[0] = vec_sum*(rand() / (RAND_MAX +1.0));
	vectors[centers[0]].isMedoid = 1;
	centers_count = 1;

	while(centers_count<k){
		for(i=0; i<k; i++)					// Arxikopoioume ta P[i] gia mia eidiki periptwsi
			P[i] = 0.0;

		for(i=0; i<vec_sum; i++){			// Gia kathe simeio
			if(vectors[i].isMedoid == 0){	// Pou den einai kentroides
				D[i] = manhattan_distance(vectors[i], vectors[centers[0]], coords);	// Ypologismos D[i]
				for(j=1; j<centers_count; j++){
					dist = manhattan_distance(vectors[i], vectors[centers[j]], coords);
					if(dist < D[i])
						D[i] = dist;
				}
				if(i==0)			// Count P[i]
					P[0] = D[0]*D[0];
				else
					P[i] = P[i-1] + D[i]*D[i];
			}else if(i>0){		// Etsi px an to dianusma 10 einai centroid to P[10] tha periexei to P[9]
				P[i] = P[i-1];	// Etsi otan to 11 dianusma otan paei paei na kanei P[11] = P[10] + D[11]^2 tha parei swsti timi
			}
		}
		max = P[0];
		for(i=1; i<vec_sum; i++){
			if(vectors[i].isMedoid == 0 && P[i]>max){
				max = P[i];
			}
		}
		for(i=0; i<vec_sum; i++){
			P[i] = P[i]/max;
		}
		random = 1.0*(rand() / (RAND_MAX +1.0));
		i=0;
		while(1){
			if(random<=P[i] && vectors[i].isMedoid == 0){
				centers[centers_count++] = i;
				vectors[i].isMedoid = 1;
				break;
			}
			i++;
		}
	}
}
