#include <stdlib.h>
#include "structs.h"
#include "functions.h"


int search(int curves_sum, struct curve *curves, struct curve query, double *distanceTrue){
	int i, j, min, min_pos;
	double dist;

	min=1000000;
	min_pos=-1;
	for(i=0; i<curves_sum; i++){		// Vriskoume ton actual kontinotero geitona tou query
		dist = dtw(curves[i], query);
		if(min>dist && dist!=0){
			min=dist;
			min_pos=i;
		}
	}
	*distanceTrue=min;			// Ekxwroume tin actual min distance		
	return min_pos;				// Epistrefoume to pos tou actual neighbor
}
