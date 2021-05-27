#include <stdlib.h>
#include "structs.h"
#include "functions.h"

#include <stdio.h>

void snap(struct curve *curves, int ****grid_curves, int **grids, int curves_sum, int grid_length, int L_grid){
	int i, j, z, p, minVal_x, minVal_y, min_x, min_y;

	for(j=0; j<L_grid; j++){
		for(i=0; i<curves_sum; i++){
			for(z=0; z<curves[i].noPoints; z++){
				min_x = grids[j][0];
				minVal_x = abs( grids[j][0]-curves[i].points[z].x*1000 );
				min_y = grids[j][0];
				minVal_y = abs( grids[j][0]-curves[i].points[z].y*1000 );
				for(p=1; p<grid_length; p++){
					if(abs( grids[j][p]-curves[i].points[z].x*1000 ) < minVal_x){
						minVal_x = abs (grids[j][p]-curves[i].points[z].x*1000);
						min_x = grids[j][p];
					}
					if(abs( grids[j][p]-curves[i].points[z].y*1000 ) < minVal_y){
						minVal_y = abs (grids[j][p]-curves[i].points[z].y*1000);
						min_y = grids[j][p];
					}
				}
				grid_curves[j][i][z][0] = min_x;
				grid_curves[j][i][z][1] = min_y;
			}
		}
	}
}
