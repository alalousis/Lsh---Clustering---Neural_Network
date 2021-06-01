#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void configuration(char path[256], int *k_clusters, int *L, int *k_lsh, char *vec_init, char *vec_asign, char *vec_upd){
	char ch, *num;
	int line, z;
	FILE *fp;
	fp = fopen(path,"r");
	num = malloc(5*sizeof(char));

	line = 1;
	while(1){
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}
		else if(ch==':'){
			ch = fgetc(fp); 		//Diavazei to keno
			ch = fgetc(fp); 
			z=0;
			while(ch != '\n'){		
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';
			if(line == 1){	
				(*k_clusters) = atoi(num);
			}
			else if(line == 2){	
				(*L) = atoi(num);
			}
			else if(line == 3){	
				(*k_lsh) = atoi(num);
			}
			else if(line == 4){	
				(*vec_init) = atoi(num);
			}
			else if(line == 5){	
				(*vec_asign) = atoi(num);
			}
			else if(line == 6){	
				(*vec_upd) = atoi(num);
			}
			line++;
		}
	}		
		
}

void save_vecs(char path[256], struct vec *vectors, int vec_sum, int coords){
	int i, j, z;
	char ch, *num;
	FILE *fp;
	
	num = malloc(30*sizeof(char));
	fp = fopen(path,"r");			// Anoigoume to arxeio wste auti ti fora na apothikeusoume ta dianusmata
	 
	z=0;
	j=0;
	i=0;

	for(i=0; i<vec_sum; i++){
		z=0;
		ch = fgetc(fp);
		while(ch != ','){			//prospername thn prwth sthlh	
			num[z] = ch;
			z++;				
			ch = fgetc(fp);
		}
		num[z] = '\0';
		strcpy(vectors[i].id, num);

		for(j=0; j<coords; j++){
			z=0;
			ch =  fgetc(fp);
			while(ch != ',' && ch != '\n'){
				num[z] = ch;
				z++;			
				ch = fgetc(fp);
			}
			num[z] = '\0';
			vectors[i].coord[j] = atof(num);
		
		}

	}

	fclose(fp);
}
