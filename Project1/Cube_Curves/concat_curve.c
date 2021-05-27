#include "structs.h"

void concat_curve(struct vec **vectors, struct curve *curves, int ****grid_curves, int curves_sum, int max_points, int L_grid){
	int i, j, z, count, last_x, last_y;

	for(i=0; i<L_grid; i++){
		for(j=0; j<curves_sum; j++){
			vectors[i][j].id = curves[j].id;
			count = 0;
			last_x = 0;
			last_y = 0;
			for(z=0; z<curves[j].noPoints; z++){
				if(grid_curves[i][j][z][0]!=last_x || grid_curves[i][j][z][1]!=last_y){
					vectors[i][j].coord[count] = grid_curves[i][j][z][0];
					vectors[i][j].coord[count+1] = grid_curves[i][j][z][1];
					last_x = grid_curves[i][j][z][0];
					last_y = grid_curves[i][j][z][1];
					count +=2;
				}
			}
			for(z=count; z<max_points*2; z++){
				vectors[i][j].coord[z] = 99999;
			}
		}
	}
}
