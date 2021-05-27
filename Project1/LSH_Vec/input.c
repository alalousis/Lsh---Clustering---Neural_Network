#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void count_input(char path[256], int *vec_sum, int *coords){
	char ch;
	FILE *fp;

	fp = fopen(path,"r");
	(*coords)=0;
	(*vec_sum)=0;
	while(1){						// Sarwnoume to arxeio metrwntas posa dianusmata exei
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			(*vec_sum)++;
		}else if((ch==' ') && ((*vec_sum)==0)){
			(*coords)++;			// Metrame poses suntentagmenes exei to 1o dianusma (toses tha exoun ola)
		}
	}
	(*coords)--;					// Exoume metrisei kai to id tou dianusmatos san suntetagmeni opote to afairoume

	fclose(fp);
}

void save_input(char path[256], struct vec *vectors){
	int i, j, z, flag;
	char ch, *num;
	FILE *fp;

	num =malloc(10*sizeof(char));	// Ara oi suntetagmenes einai mexri 9psifioi arithmoi
	fp = fopen(path,"r");			// Ksana anoigoume to arxeio wste autoi ti fora na apothikeusoume ta dianusmata
	flag=0;
	z=0;
	j=0;
	i=0;
	while(1){
		ch = fgetc(fp);
		if(ch==EOF){
			break;
		}else if(ch=='\n'){
			i++;
			j=0;
			flag=0;
		}else if(ch==' '){
			z=0;
			if(flag){				// An i flag einai 0 tote to num periexei to id tou dianusmatos (oxi kapoia suntetagmeni)
				vectors[i].coord[j]=atoi(num);
				j++;
			}else{
				vectors[i].id=atoi(num);
				flag=1;
			}
		}else{
			num[z++]=ch;
			num[z]='\0';
		}	
	}
	fclose(fp);
}
