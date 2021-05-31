#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void configuration(char path[256], int *k_clusters, int *grids, int *L, int *k_lsh){
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
			while(ch != '\n'){		//Apothikeuoume to id tou kathe curve
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';
			if(line == 1){	
				(*k_clusters) = atoi(num);
			}
			else if(line == 2){	
				(*grids) = atoi(num);
			}
			else if(line == 3){	
				(*L) = atoi(num);
			}
			else if(line == 4){	
				(*k_lsh) = atoi(num);
			}
			line++;
		}
	}		
		
}


void count_vecs(char path[256], int *vec_sum, int *coords){
	char ch;
	FILE *fp;

	fp = fopen(path,"r");
	while(1){						// Prospername tin 1i leksi (vectors)
		ch = fgetc(fp);
		if(ch=='\n')
			break;
	}

	(*coords)=0;
	(*vec_sum)=0;
	while(1){						// Sarwnoume to arxeio metrwntas posa dianusmata exei
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			(*vec_sum)++;
		}else if(( ch=='\t'||ch==' ' ) && ((*vec_sum)==0)){
			(*coords)++;			// Metrame poses suntentagmenes exei to 1o dianusma (toses tha exoun ola)
		}
	}

	fclose(fp);
}

void save_vecs(char path[256], struct vec *vectors){
	int i, j, z, flag;
	char ch, *num;
	FILE *fp;

	num =malloc(30*sizeof(char));
	fp = fopen(path,"r");			// Ksana anoigoume to arxeio wste autoi ti fora na apothikeusoume ta dianusmata
	while(1){						// Prospername tin 1i leksi (vectors)
		ch = fgetc(fp);
		if(ch=='\n')
			break;
	}
	flag=0;
	z=0;
	j=0;
	i=0;
	while(1){
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			z=0;
			vectors[i].coord[j]=atof(num);
			i++;
			j=0;
			flag=0;
		}else if(ch=='\t' || ch==' '){
			z=0;
			if(flag){				// An i flag einai 0 tote to num periexei to id tou dianusmatos (oxi kapoia suntetagmeni)
				vectors[i].coord[j]=atof(num);
				j++;
			}else{
				strcpy(vectors[i].id, num);
				//vectors[i].id=atoi(num);
				flag=1;
			}
		}else{
			num[z++]=ch;
			num[z]='\0';
		}	
	}
	fclose(fp);
}

int count_curves(char path[256]){
	int curves_sum;
	char ch;
	FILE *fp;

	fp = fopen(path,"r");
	while(1){						// Prospername tin 1i leksi (curves)
		ch = fgetc(fp);
		if(ch=='\n')
			break;
	}

	curves_sum=0;
	while(1){						// Sarwnoume to arxeio metrwntas posa curves exei
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			curves_sum++;
		}
	}

	fclose(fp);
	return curves_sum;
}

int save_curves (char path[256], struct curve *curves, int curves_sum){
	int i, j, z, max;
	char ch, *num;
	FILE *fp;
	num = malloc(25*sizeof(char));

	fp = fopen(path,"r");
	max = 0;
	i=0;
	z=0;

	while(i < curves_sum){						// Sarwnoume to arxeio metrwntas posa curves exei
		curves[i].isMedoid = 0;
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}
		else if(ch=='\n'){				//Apothikeuoume to plithos twn suntetagmenwn gia kathe curve
			z=0;
			ch = fgetc(fp);
			while(ch != '\t' && ch != ' '){		//Apothikeuoume to id tou kathe curve
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';	
			curves[i].id = atoi(num);

			z=0;	
			ch = fgetc(fp);				//Apothikeuoume to plithos twn shmeiwn tou kathe curve
			while(ch != '\t' && ch != ' '){		
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';	
			curves[i].noPoints = atoi(num);
			if (curves[i].noPoints > max){
				max = curves[i].noPoints;
			}
			curves[i].points = malloc(curves[i].noPoints*sizeof(struct point));	//Apothikeuoume ta shmeia tou kathe curve				
			for(j=0; j<curves[i].noPoints; j++){
				z=0;
				ch = fgetc(fp);				//Diavazei thn parenthesi '('
				ch = fgetc(fp);				//Diavazei to ptwto psifio tou x
				while(ch != '\t' && ch != ' '){		//Apothikeuei to x
					num[z] = ch;
					z++;
					ch = fgetc(fp);
				}
				num[z] = '\0';
				curves[i].points[j].x = atof(num);

				z=0;
				ch = fgetc(fp);				//Diavazei to ptwto psifio tou y
				while(ch != ')' && ch != ' '){		//Apothikeuei to y
					num[z] = ch;
					z++;
					ch = fgetc(fp);
				}
				num[z] = '\0';	
				curves[i].points[j].y = atof(num);
				ch = fgetc(fp);					//Diavazei eite SPACE eite CR
			}
			
			i++;
		}
	} 
	fclose(fp);
	return max;
}
