#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void vec_write_output(char path[256], struct vec *vectors, struct vec *centers, int vec_sum, int k, int vec_upd, double *s, int coords, double time){
	int i, j, *size;
	double *s_cluster, s_total;
	FILE *fp;
	
	fp = fopen(path, "w");
	
	size = malloc(k*sizeof(int));
	s_cluster = malloc(k*sizeof(int));
	s_total = 0; 

	for(i=0; i<k; i++){
		size[i] = 0;
		s_cluster[i] = 0;
		for(j=0; j<vec_sum; j++){
			if(vectors[j].nearest == i){
				size[i]++;
				s_cluster[i] += s[j];
			}
			s_total += s[j];
		}
		s_cluster[i] = s_cluster[i] / size[i];
	}
	s_total = s_total / vec_sum;

	if (vec_upd == 1){
		for(i=0; i<k; i++){
			fprintf(fp, "CLUSTER-%d {size: %d,  centroid: %s}", i+1, size[i], centers[i].id);
			fprintf(fp, "\n\n");
		}
	}
	else if(vec_upd == 2){
		for(i=0; i<k; i++){
			fprintf(fp, "CLUSTER-%d {size: %d,  ", i+1, size[i]);
			for(j=0; j<coords; j++){
				fprintf(fp, "%f, ", centers[i].coord[j]);
			}
			fprintf(fp, "}");
			fprintf(fp, "\n\n");
		}
	}
	
	fprintf(fp, "clustering_time: %f\n\n", time);
	fprintf(fp, "Silhouette: [");
	for(i=0; i<k; i++){
		fprintf(fp, "%f, ", s_cluster[i]);
	}
	fprintf(fp, "%f]\n", s_total);
	
}

void curve_write_output(char path[256], struct curve *curves, struct curve *centers, int curves_sum, int k, double *s, double time){
	int i, j, *size;
	double *s_cluster, s_total;
	FILE *fp;
	
	fp = fopen(path, "w");
	
	size = malloc(k*sizeof(int));
	s_cluster = malloc(k*sizeof(int));
	s_total = 0; 

	for(i=0; i<k; i++){
		size[i] = 0;
		s_cluster[i] = 0;
		for(j=0; j<curves_sum; j++){
			if(curves[j].nearest == i){
				size[i]++;
				s_cluster[i] += s[j];
			}
			s_total += s[j];
		}
		s_cluster[i] = s_cluster[i] / size[i];
	}
	s_total = s_total / curves_sum;

	for(i=0; i<k; i++){
		fprintf(fp, "CLUSTER-%d {size: %d,  ", i+1, size[i]);
		for(j=0; j<centers[i].noPoints; j++){
			fprintf(fp, "(%f, %f) ", centers[i].points[j].x, centers[i].points[j].y);
		}
		fprintf(fp, "}");
		fprintf(fp, "\n\n");
	}

	fprintf(fp, "clustering_time: %f\n\n", time);
	fprintf(fp, "Silhouette: [");
	for(i=0; i<k; i++){
		fprintf(fp, "%f, ", s_cluster[i]);
	}
	fprintf(fp, "%f]\n", s_total);
	
}
