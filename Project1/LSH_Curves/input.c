#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

int count_curves(char path[256]){
	int curves_sum;
	char ch;
	FILE *fp;

	fp = fopen(path,"r");
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


int count_points (char path[256], struct curve *curves){
	int i, z, max;
	char ch, *num;
	FILE *fp;
	num = malloc(10*sizeof(char));
	fp = fopen(path,"r");
	max = 0;
	i=0;
	z=0;
	while(1){						// Sarwnoume to arxeio metrwntas posa curves exei
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}
		else if(ch=='\t'){				//Apothikeuoume to plithos twn suntetagmenwn gia kathe curve
			z=0;
			ch = fgetc(fp);
			while(ch != '\t'){
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';	
			curves[i].noPoints = atoi(num);
			curves[i].id = i;
			if(curves[i].noPoints>max){
				max = curves[i].noPoints;
			}
			ch = fgetc(fp);
		}
		else if(ch=='\n'){
			i++;
		}
	} 
	fclose(fp);
	return max;
}


void save_input(char path[256], struct curve *curves){
	int i, j, z;
	char ch, *num;
	FILE *fp;

	num =malloc(25*sizeof(char));		// Ara oi suntetagmenes einai mexri 9psifioi arithmoi
	fp = fopen(path,"r");			// Ksana anoigoume to arxeio wste autoi ti fora na apothikeusoume ta dianusmata
	z=0;
	j=0;
	i=0;
	while(1){
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='('){
			ch = fgetc(fp);
			z=0;
			while(ch != ','){				//Diavazetai h suntetagmenh x
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';
			curves[i].points[j].x = atof(num);		
			ch = fgetc(fp);					//Diavazetai to comma
			z=0;
			ch = fgetc(fp);
			while(ch != ')'){				//Diavazetai h suntetagmenh y
				num[z] = ch;
				z++;
				ch = fgetc(fp);
			}
			num[z] = '\0';
			curves[i].points[j].y = atof(num);
			j++;
				
		}else if(ch=='\n'){
			i++;
			j=0;

		}
	}
	fclose(fp);
}
