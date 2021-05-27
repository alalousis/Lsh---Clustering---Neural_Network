#include "structs.h"
#include "functions.h"

double count_d(struct curve *curves, int curves_sum){
	int i, j;
	double sum, average_sum, d;

	average_sum = 0.0;
	for(i=0; i<curves_sum; i++){
		sum = 0.0;
		for(j=0; j<curves[i].noPoints-1; j++){
			sum += euclidean(curves[i].points[j], curves[i].points[j+1]);
		}
		if(curves[i].noPoints != 1){
			average_sum += sum/(curves[i].noPoints-1.0);
		}
	}
	d = average_sum / curves_sum;

	return d;
}
