#include <stdlib.h>
#include "headers.h"

unsigned int concut(struct h_func *z, int k){
	int i;
	unsigned int g=0;
	for(i=0; i<k; i++){
		g+= z[i].h_sum << (32 - (32/k)*(i+1));	// Kanoume tin parathesi g=[h0|h1|...|hk]				
	}
	
	return g;
}
