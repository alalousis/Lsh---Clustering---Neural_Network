#include <stdlib.h>
#include "structs.h"
#include "functions.h"

#include <stdio.h>	////

double dtw(struct curve a, struct curve b, struct pair **traversal, char compute_traversal){
	int i, j;
	double dist;
	struct dtw_cell **dtw_table, *min;
	
	dtw_table = malloc(a.noPoints * sizeof(struct dtw_cell *));
	for(i=0; i<a.noPoints; i++){
		dtw_table[i] = malloc(b.noPoints * sizeof(struct dtw_cell));
		for(j=0; j<b.noPoints; j++){
			dtw_table[i][j].previous = NULL;
			dtw_table[i][j].x = i;
			dtw_table[i][j].y = j;
		}
	}

	dtw_table[0][0].value = euclidean(a.points[0], b.points[0]);
	for(i=1; i<a.noPoints; i++){								//Arxikopoioume thn prwth sthlh
		dtw_table[i][0].value = euclidean(a.points[i], b.points[0]) + dtw_table[i-1][0].value;
		dtw_table[i][0].previous = &(dtw_table[i-1][0]);
	}
	
	for(j=1; j<b.noPoints; j++){								//Arxikopoioume thn prwth grammh
		dtw_table[0][j].value = euclidean(a.points[0], b.points[j]) + dtw_table[0][j-1].value;
		dtw_table[0][j].previous = &(dtw_table[0][j-1]);
	}
	
	for(i=1; i<a.noPoints; i++){
		for(j=1; j<b.noPoints; j++){
			min = min_neighbour( &(dtw_table[i-1][j]), &(dtw_table[i-1][j-1]), &(dtw_table[i][j-1]));
			dtw_table[i][j].value = min->value + euclidean(a.points[i], b.points[j]);
			dtw_table[i][j].previous = min;
		}
	}

	dist = dtw_table[a.noPoints-1][b.noPoints-1].value;
	if(compute_traversal)
		backtracking(dtw_table, traversal, a.noPoints, b.noPoints);
	
	for(i=0; i<a.noPoints; i++){
		free(dtw_table[i]);
	}
	free(dtw_table);

	return dist;
}
	
struct dtw_cell *min_neighbour(struct dtw_cell *a, struct dtw_cell *b, struct dtw_cell *c){
	if(a->value < b->value){
		if(a->value <= c->value){
			return a;
		}else{
			return c;
		}
	}else{
		if(b->value <= c->value){
			return b;
		}else{
			return c;
		}
	}
}

void backtracking(struct dtw_cell **dtw_table, struct pair **traversal, int x_border, int y_border){
	int i, noPairs;
	struct dtw_cell *cur;
	
	noPairs= 1;
	cur = &(dtw_table[x_border-1][y_border-1]);
	while(cur->previous != NULL){
		cur = cur->previous;
		noPairs++;
	}
	
	(*traversal) = malloc((noPairs+1)*sizeof(struct pair));
	(*traversal)[0].one = noPairs;		// Paradoxi wste na epistrefw to noPairs

	cur = &(dtw_table[x_border-1][y_border-1]);
	for(i=0; i<noPairs; i++){
		(*traversal)[noPairs-i].one = cur->x;
		(*traversal)[noPairs-i].two = cur->y;
		cur = cur->previous;
	}
}


