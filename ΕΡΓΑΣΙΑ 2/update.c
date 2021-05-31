#include <stdlib.h>
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

	prev_cent.coord = malloc(coords*sizeof(int));

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
			for(j=0; j<coords; j++)
				centers[i].coord[j] = centers[i].coord[j] / cluster_size;
	
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

void Initialize_C(struct curve *curves, struct curve *centers_curve, struct curve *C, int curves_sum, int k){
	int i, j, lamda, n, random_sequence, sequence_num, counter, flag;
	
	for(i=0; i<k; i++){
		lamda = 0;						//Ypologizoume to lamda
		n=0;
		for(j=0; j<curves_sum; j++){
			if(curves[j].nearest == i){
				lamda += curves[j].noPoints;
				n++;
			}
		}
		lamda = lamda/n;
		srand(time(0));						//Vriskoume thn tuxaia upoakolouthia
		flag = 1;
		do{
			random_sequence = n*(rand() / (RAND_MAX +1.0));
			counter=-1;
			for(j=0; j<curves_sum; j++){
				if(curves[j].nearest == i){
					counter++;
					if(counter == random_sequence){		//Eimaste sthn tuxaia akolouthia S0
						if(curves[j].noPoints >= lamda){
							flag = 0;
							sequence_num = j;
						}
						break;
					}
				}
			}
		}while(flag);

		random_subsequence(curves[sequence_num], &(C[i]), lamda);
		
	}
}

void random_subsequence(struct curve a, struct curve *b, int lamda){
	int i, *random_points;

	random_points = malloc(lamda*sizeof(int));
	srand(time(0));
	random_points[0] = 0;
	for(i=1; i<lamda; i++){
		do{
			random_points[i] = a.noPoints*(rand() / (RAND_MAX +1.0));
		}while(random_points[i] <= random_points[i-1] || random_points[i] > a.noPoints-(lamda-i));
	}

	b->noPoints = lamda;
	for(i=0; i<lamda; i++){
		b->points[i].x = a.points[random_points[i]].x;
		b->points[i].y = a.points[random_points[i]].y;
	}
}

void DBA(struct curve *curves, struct curve *C,  int curves_sum, int k, int max_points){
	int i, j, z, count, num_pairs, *paired_points, flag, changes, total_points;
	double dist;
	struct curve *prevC, *newC;
	struct pair *traversal;

	paired_points = malloc(max_points*sizeof(int));
	for(i=0; i<max_points; i++)
		paired_points[i] = 0;
	prevC = malloc(k*sizeof(struct curve));
	for(i=0; i<k; i++){
		prevC[i].points = malloc(max_points*sizeof(struct point));
		prevC[i].noPoints = C[i].noPoints;
	}
	
	newC = malloc(k*sizeof(struct curve));
	for(i=0; i<k; i++){
		newC[i].points = malloc(max_points*sizeof(struct point));
		newC[i].noPoints = C[i].noPoints;
		for(j=0; j<C[i].noPoints; j++){
			newC[i].points[j].x = 0.0;
			newC[i].points[j].y = 0.0;
		}
	}

	flag = 1;
	count = 0;
	while(count < 100 && flag){
		changes = 0;
		total_points = 0;
		for(i=0; i<k; i++){
			for(j=0; j<curves_sum; j++){
				if(curves[j].nearest == i){
					dist = dtw(C[i], curves[j], &traversal, 1);
					num_pairs = traversal[0].one;
					for(z=1; z<num_pairs+1; z++){
						newC[i].points[traversal[z].one].x += curves[j].points[traversal[z].two].x;
						newC[i].points[traversal[z].one].y += curves[j].points[traversal[z].two].y;
						paired_points[traversal[z].one]++;
					}
					free(traversal);
				}
			}
			for(j=0; j<C[i].noPoints; j++){
				prevC[i].points[j].x = C[i].points[j].x;
				prevC[i].points[j].y = C[i].points[j].y;
			}
			for(j=0; j<C[i].noPoints; j++){
				C[i].points[j].x = newC[i].points[j].x / paired_points[j];
				C[i].points[j].y = newC[i].points[j].y / paired_points[j];
				newC[i].points[j].x = 0.0;
				newC[i].points[j].y = 0.0;
				paired_points[j] = 0;
			}
			for(j=0; j<C[i].noPoints; j++){
				if(prevC[i].points[j].x != C[i].points[j].x || prevC[i].points[j].y != C[i].points[j].y){
					changes++;
				}
			}
			total_points += C[i].noPoints;
		}
		Lloyds_assignment_curve(curves, C, curves_sum, k);

		if(changes < total_points/20)	// An allaxoun ligotera apo 5% twn kentrwn
			flag = 0;
		count++;
	}
	

}
