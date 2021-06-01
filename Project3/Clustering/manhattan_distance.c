#include <stdlib.h>
#include "structs.h"

double manhattan_distance(struct vec a, struct vec b, int coords){
	int i;
	double distance;

	distance= 0.0;
	for(i=0; i<coords; i++){
		if(a.coord[i]>b.coord[i])
			distance += a.coord[i]-b.coord[i];
		else
			distance += b.coord[i]-a.coord[i];
	}

	return distance;
}
