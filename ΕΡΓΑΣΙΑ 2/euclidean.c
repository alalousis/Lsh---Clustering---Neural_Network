#include <math.h>
#include "structs.h"

double euclidean(struct point a, struct point b){
	return pow( pow(a.x - b.x, 2) + pow(a.y - b.y, 2), 0.5 );
}
