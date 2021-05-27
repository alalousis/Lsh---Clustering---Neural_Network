#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "structs.h"
#include "functions.h"

int main (int argc, char *argv[]){
	int i, j, z, p, curves_sum, max_points, **grids, ****grid_curves, ****grid_queries, k_hypercube, L_grid, delta, **t, grid_length, quer_sum;	// For curves
	int m, M,  *search_results, *cube_results, *cur_cube_results, **h_sum, *h_quer, M_Cube, probes, d, w, *m_factors;					// For cube
	double e, *distanceTrue, *distanceCube, *cur_distanceCube;
	char input[256], query[256], output[256];
	struct curve *curves, *queries;
	struct vec **vectors, **vectors_quer;
	struct list_node ***f, ***cube;
	struct h_func *h;
	
	if(argc==11){					// Pairnoume ta orismata
		strcpy(input, argv[2]);
		strcpy(query, argv[4]);
		k_hypercube = atoi(argv[6]);
		M_Cube = atoi(argv[8]);
		e = atof(argv[10]);
		L_grid = atoi(argv[12]);
		strcpy(output, argv[14]);
	
	}else{							// An den itan arketa diavazoume ta files ap to pliktrologio							
//		printf("Give the path to the input file:\n");
//		scanf("%s", input);
//		printf("Give the path to the query file:\n");
//		scanf("%s", query);
//		printf("Give the path to the output file:\n");
//		scanf("%s", output);
		strcpy(input, "trajectories_dataset");
		k_hypercube = 4;
		L_grid = 4;
		e = 0.5;
	}
	
	printf("Reading curves...\n");
	curves_sum = count_curves(input);							// Metrame to plithos twn curves
	curves = malloc(curves_sum*sizeof(struct curve));
	max_points = count_points(input, curves);					// Metrame to plithos twn suntetagmenwn kathe curve
	for(i=0; i<curves_sum; i++){
		curves[i].points = malloc(curves[i].noPoints*sizeof(struct point));
	}	
	save_input(input, curves);

	quer_sum = 100;										// Efoson den trexei swsta o kwdikas den eftasa sto simeio na diabazw ta queries

	delta=2;
	grid_length = 2000;

	curves_sum = 1000;	

	printf("Calculating Grids...\n");
	grids = malloc(L_grid*sizeof(int *));				// Kanoume malloc gia ta grids
	for(i=0; i<L_grid; i++){
		grids[i] = malloc(grid_length*sizeof(int));
	}
	for(i=0; i<L_grid; i++){							// Ta gemizoume
		z = -7000;
		for(j=0; j<grid_length/2; j++){
			grids[i][j] = z;
			z++;
		}
		z = 53000;
		for(j=grid_length/2; j<grid_length; j++){
			grids[i][j] = z;
			z++;
		}
	}

	srand(time(0));
	t = malloc(L_grid*sizeof(int *));					// Ypologizoume kai prosthetoume ta t
	for(i=0; i<L_grid; i++){
		t[i] = malloc(grid_length*sizeof(int));
		for(j=0; j<grid_length; j++){
			t[i][j] = delta * (rand() / (RAND_MAX +1.0));
			grids[i][j] += t[i][j];
		}
	}

	grid_curves = malloc(L_grid*sizeof(int ***));		// Kanw malloc tis kampules pou tha bgoun ap ta snap
	for(i=0; i<L_grid; i++){
		grid_curves[i] = malloc(curves_sum*sizeof(int **));
		for(j=0; j<curves_sum; j++){
			grid_curves[i][j] = malloc(curves[j].noPoints*sizeof(int *));
			for(z=0; z<curves[j].noPoints; z++){
				grid_curves[i][j][z] = malloc(2*sizeof(int));
			}
		}
	}

	printf("Snaping...\n");
	snap(curves, grid_curves, grids, curves_sum, grid_length, L_grid);

	vectors = malloc(L_grid*sizeof(struct vec *));
	for(i=0; i<L_grid; i++){
		vectors[i] = malloc(curves_sum*sizeof(struct vec));
		for(j=0; j<curves_sum; j++){
			vectors[i][j].coord = malloc(max_points*2*sizeof(int));
		}
	}
	concat_curve(vectors, curves, grid_curves, curves_sum, max_points, L_grid);
int dok=0;
	for(j=0; j<10; j++){
		for(z=0; z<2*max_points; z++){
			if( vectors[0][j].coord[z]==vectors[1][j].coord[z] && vectors[1][j].coord[z]!=99999){
				dok++;
			}
		}
		printf("Curve %d: %d / %d\n", j, dok, curves[j].noPoints);
		dok = 0;
	}
	for(i=0; i<L_grid; i++){
		for(j=0; j<11; j++){
			printf("%d ", vectors[i][6].coord[j]);
		}
		printf("\n");
	}

	grid_queries = malloc(L_grid*sizeof(int ***));		// Kanw malloc tis kampules twn queries pou tha bgoun ap ta snap
	for(i=0; i<L_grid; i++){
		grid_queries[i] = malloc(quer_sum*sizeof(int **));
		for(j=0; j<quer_sum; j++){
			grid_queries[i][j] = malloc(curves[j].noPoints*sizeof(int *));
			for(z=0; z<curves[j].noPoints; z++){
				grid_queries[i][j][z] = malloc(2*sizeof(int));
			}
		}
	}
	printf("Snaping queries...\n");
//	snap(queries, grid_queries, grids, quer_sum, grid_length, L_grid);			Gia otan tha diabazoume swsta ta queries
	snap(curves, grid_queries, grids, quer_sum, grid_length, L_grid);

	vectors_quer = malloc(L_grid*sizeof(struct vec *));
	for(i=0; i<L_grid; i++){
		vectors_quer[i] = malloc(quer_sum*sizeof(struct vec));
		for(j=0; j<quer_sum; j++){
			vectors_quer[i][j].coord = malloc(max_points*2*sizeof(int));
		}
	}
	concat_curve(vectors_quer, curves, grid_curves, quer_sum, max_points, L_grid);


	probes = 25;
	d = log2(curves_sum);
	search_results = malloc(quer_sum*sizeof(int));
	cube_results = malloc(quer_sum*sizeof(int));
	cur_cube_results = malloc(quer_sum*sizeof(int));
	distanceTrue = malloc(quer_sum*sizeof(double));
	distanceCube = malloc(quer_sum*sizeof(double));
	cur_distanceCube = malloc(quer_sum*sizeof(double));
	h_sum = malloc(curves_sum*sizeof(int *));
	for(i=0; i<curves_sum; i++){
		h_sum[i] = malloc(d*sizeof(int));
	}
	f = malloc(d*sizeof(struct list_node **));
	for(i=0; i<d; i++){
		f[i] = malloc(4999*sizeof(struct list_node *));
	}

	for(i=0; i<d; i++){
		for(j=0; j<4999; j++){
			f[i][j] = NULL;
		}
	}

	printf("Searching full...\n");
	for(i=0; i<quer_sum; i++){
	//	search_results[i] = search(curves_sum, curves, queries[i], &distanceTrue[i]);	// Kwdikas exantlitikis anazitisis
		search_results[i] = search(curves_sum, curves, curves[i], &distanceTrue[i]);
	}
	printf("0 -> %d\t1 -> %d\n", search_results[0], search_results[1]);

	h = malloc(d*sizeof(struct h_func));		// Ftiaxnoume tis sunartiseis h pou kathe mia tha exei ola ta s apothikeumena gia to query
	for(i=0; i<d; i++){	
		h[i].s = malloc(max_points*2*sizeof(int));
	}

	cube = malloc(L_grid*sizeof(struct list_node **));
	for(i=0; i<L_grid; i++){
		cube[i] = malloc(curves_sum*sizeof(struct list_node *));
		for(j=0; j<curves_sum; j++){
			cube[i][j] = NULL;
		}
	}

	srand(time(0));								// Dinoume tuxaies times sta s sto diastima [0,w)
	for(i=0; i<d; i++){
		for(z=0; z<max_points*2; z++){
			h[i].s[z] = w*(rand() / (RAND_MAX +1.0));
		}
	}
	m = 5;										// Ekxwroume times sta m, M
	M = pow(2, 32/k_hypercube);

	m_factors = malloc(max_points*2*sizeof(int));		// Apothikeuoume ola ta (m^d) mod M, gia na min kanoume askopous upologismous
	factors(m, M, max_points*2, m_factors);

	printf("Training Cube...\n");
	for(i=0; i<L_grid; i++){
		lsh_train(vectors[i], h, m_factors, h_sum, curves_sum, max_points*2, M, d, w);	// Ekteloume to lsh gia to input data
		cube_train(h_sum, f, cube[i], curves_sum, d);										// Ekteloume to cube gia to input data
	}
	
	h_quer = malloc(d*sizeof(int));
	for(i=0; i<quer_sum; i++){
		distanceCube[i] = -1.0;
	}

	printf("Cube Search...\n");
	for(i=0; i<quer_sum; i++){
		for(j=0; j<L_grid; j++){
			lsh_search(vectors_quer[j][i], h, m_factors, h_quer, max_points*2, M, d, w);	// Ekteloume lsh gia ta queries
			cur_cube_results[i] = cube_search(h_quer, f, cube[j], curves, curves[i], &cur_distanceCube[i], curves_sum, max_points*2, d, probes, M_Cube);
			printf("distanceCube[%d] = %f\tcur_distanceCube[%d] = %f\n", i, distanceCube[i], i, cur_distanceCube[i]);
			if(distanceCube[i] == -1.0 || cur_distanceCube[i] < distanceCube[i]){
				distanceCube[i] = cur_distanceCube[i];
				cube_results[i] = cur_cube_results[i];
				//printf("distanceCube[%d] = %f\n", i, distanceCube[i]);
			}
		}
		printf("%d -> %d\n", i, cube_results[i]);
	}

	int correct;
	correct=0;
	for(i=0; i<quer_sum; i++){
		if(cube_results[i]==search_results[i]){
			correct++;
		}
	}
	printf("Results: %d / 100\n", correct);

	return 0;
}
