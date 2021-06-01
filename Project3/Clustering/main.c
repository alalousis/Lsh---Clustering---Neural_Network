#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

int main(int argc, char* argv[]){
	int i, j, z, vec_sum, coords, c, k, L, k_lsh, w, m, M, *m_factors;
	double  *s;
	time_t start, stop, final_time;
	char input[256], conf[256], output[256], ch, vec_init, vec_asign, vec_upd;
	struct vec *vectors, *centers;
	struct h_func **h; 
	struct list_node ***HashTables;
	
	if(argc==7){					// Pairnoume ta orismata
		strcpy(input, argv[2]);
		strcpy(conf, argv[4]);
		strcpy(output, argv[6]);
	
	}else{							// An den itan arketa diavazoume ta files ap to pliktrologio					
		printf("Give the path to the input file:\n");
		scanf("%s", input);
		printf("Give the path to the conf file:\n");
		scanf("%s", conf);
		printf("Give the path to the output file:\n");
		scanf("%s", output);
	}

	/******* Read conf file *******/
	configuration(conf, &k, &L, &k_lsh, &vec_init, &vec_asign, &vec_upd);
	
	vec_sum = 23988;
	if(strcmp(input, "nn_representations.csv") == 0){
		coords = 128;
	}
	else if(strcmp(input, "new_representation.csv") == 0){
		coords = 64;
	}

	printf("vec_sum=%d  coords=%d\n", vec_sum, coords);


		/***** Input dianusmatwn *****/
	vectors = malloc(vec_sum*sizeof(struct vec));				// Kanoume malloc gia na ta apothikeusoume

	for(i=0; i<vec_sum; i++){
		vectors[i].coord = malloc(coords*sizeof(double));
		vectors[i].isMedoid = 0;
		vectors[i].nearest = -1;
	}

	save_vecs(input, vectors, vec_sum, coords);
	printf("Dataset Saved\n");	

		/****** Initialization ***********/

	start = time(0);
	centers = malloc(k*sizeof(struct vec));
	for(i=0; i<k; i++)
		centers[i].coord = malloc(coords*sizeof(double));

	if(vec_init == 1)
		random_selection(vectors, vec_sum, k);
	else
		k_means_plus_plus(vectors, vec_sum, k, coords);
	
	c = 0;
	for(i=0; i<vec_sum; i++){

		if (vectors[i].isMedoid == 1){
			for(j=0; j<coords; j++){
				centers[c].coord[j] = vectors[i].coord[j];
			}

			for(j=0; j<64; j++){
				centers[c].id[j] = vectors[i].id[j];
			}

			c++;
		}
	}

	printf("Initialization Done\n");

		/****** Assignment ***********/

	if(vec_asign == 1){
		Lloyds_assignment(vectors, centers, vec_sum, coords, k);
	}else{
		lsh_init(&w, &m, &M, &h, &HashTables, &m_factors, vec_sum, coords, k_lsh, L);		// Kanoume ta katallila malloc kai tis arxikopoiiseis
		lsh_train(vectors, h, HashTables, m_factors, vec_sum, coords, M, k_lsh, L, w, vec_sum/8);		// Ekteloume to lsh gia to input data
		LSH_assignment(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L);
	}
	printf("Assignment Done\n");

		/****** Update ***********/

	if(vec_upd == 1){
		PAM(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L, vec_asign);
	}
	else{
		PAMean(vectors, centers, h,  HashTables, m_factors, vec_sum, coords, k, k_lsh, L, vec_asign);
	}
	printf("Update Done\n");

	stop = time(0);
	final_time = stop - start;

	s = malloc(vec_sum*sizeof(double));
	vec_silhouette(vectors, vec_sum, coords, s);
	printf("Silhouette Done\n");

	vec_write_output(output, vectors, centers, vec_sum, k, vec_upd, s, coords, final_time);

	return 0;
}
