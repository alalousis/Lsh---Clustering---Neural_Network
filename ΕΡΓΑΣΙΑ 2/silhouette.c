#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

void vec_silhouette(struct vec *vectors, int vec_sum, int coords, double *s){
	int i, j, a_counter, b_counter;
	double *a, *b;

	a = malloc(vec_sum*sizeof(double));
	b = malloc(vec_sum*sizeof(double));

	for(i=0; i<vec_sum; i++){
		a_counter = -1;
		b_counter = 0;
		a[i] = 0;
		b[i] = 0;
		for(j=0; j<vec_sum; j++){
			if(vectors[i].nearest == vectors[j].nearest){
				a[i] += manhattan_distance(vectors[i], vectors[j], coords);
				a_counter++;
			}
			else if(vectors[i].second_nearest == vectors[j].nearest){
				b[i] += manhattan_distance(vectors[i], vectors[j], coords);
				b_counter++;
			}
		}

		a[i] = a[i]/a_counter;
		b[i] = b[i]/b_counter;
		if(a[i] >= b[i]){
			s[i] = (b[i] - a[i]) / a[i];
		}
		else{
			s[i] = (b[i] - a[i]) / b[i];
		}
	}
}

void curve_silhouette(struct curve *curves, int curves_sum, int coords, double *s){
	int i, j, a_counter, b_counter;
	double *a, *b;
	struct pair **traversal;

	a = malloc(curves_sum*sizeof(double));
	b = malloc(curves_sum*sizeof(double));

	for(i=0; i<curves_sum; i++){
		a_counter = -1;
		b_counter = 0;
		for(j=0; j<curves_sum; j++){
			if(curves[i].nearest == curves[j].nearest){
				a[i] += dtw(curves[i], curves[j], traversal, 0);
				a_counter++;
			}
			else if(curves[i].second_nearest == curves[j].nearest){
				b[i] += dtw(curves[i], curves[j], traversal, 0);
				b_counter++;
			}
		}

		a[i] = a[i]/a_counter;
		b[i] = b[i]/b_counter;
		if(a[i] >= b[i]){
			s[i] = (b[i] - a[i]) / a[i];
		}
		else{
			s[i] = (b[i] - a[i]) / b[i];
		}
	}
}
