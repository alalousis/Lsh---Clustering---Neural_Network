#include <stdlib.h>
#include "structs.h"
#include "functions.h"

int modulo_calc(int base, int exponent, int modulus){
	int i, result;

	result=1;				// Kwdikas gia ton upologismo tou m^d % M, xwris na ginei uperxeilisi
	for(i=0; i < exponent; i++){
		result= (result * base) % modulus;
	}
	return result;
}

void factors(int m, int M, int coords, int *m_factors){
	int j;
	for(j=0; j<coords; j++){
		m_factors[j] = modulo_calc(m, (coords-1) - j, M);			// Ypologizoume kai apothikeuoume ola ta m^(coords-1)-j % M
	}
}

unsigned int concat(struct h_func *z, int k){
	int i;
	unsigned int g=0;
	for(i=0; i<k; i++){
		g+= z[i].h_sum << (32 - (32/k)*(i+1));	// Kanoume tin parathesi g=[h0|h1|...|hk]				
	}
	
	return g;
}

void hash(struct list_node **Hash, int pos, unsigned int g, int i){
	struct list_node *cur;
	cur=Hash[pos];
	if(cur==NULL){										// Klassikos kwdikas eisagwgis se HashTable
		Hash[pos]=malloc(sizeof(struct list_node));
		Hash[pos]->next=NULL;
		Hash[pos]->g=g;
		Hash[pos]->vec_pos=i;
	}else{
		while(cur->next!=NULL){
			cur= cur->next;
		}
		cur->next= malloc(sizeof(struct list_node));
		cur->next->g=g;
		cur->next->next=NULL;
		cur->next->vec_pos=i;
	}
}
