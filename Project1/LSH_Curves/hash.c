#include <stdlib.h>
#include "structs.h"

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

