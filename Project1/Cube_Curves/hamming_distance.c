#include <math.h>

int count_edges(int start, int d, int *binary_string, int *cube_pos, int hamming_distance, int count_probes, int probes){
	int i, j;

	for(i=start; i<d; i++){
		if(binary_string[i] == 0)
			binary_string[i] = 1;
		else
			binary_string[i] = 0;
		if(hamming_distance>1){
			count_probes = count_edges(i+1, d, binary_string, cube_pos, hamming_distance-1, count_probes, probes);
		}else{
			if(count_probes>=probes){
				if(binary_string[i] == 0)
					binary_string[i] = 1;
				else
					binary_string[i] = 0;
				return count_probes;
			}
			for(j=0; j<d; j++){
				cube_pos[count_probes] += binary_string[j] * pow(2,d-1 -j);
			}
			count_probes++;
		}
		if(binary_string[i] == 0)
			binary_string[i] = 1;
		else
			binary_string[i] = 0;
	}
	return count_probes;
}

void edges(int *binary_string, int *cube_pos, int probes, int d){
	int i, j, count_probes;
	
	for(i=0; i<probes; i++){
		cube_pos[i]=0;
	}
	
	for(j=0; j<d; j++){
		cube_pos[0] += binary_string[j]*pow(2,d-1 -j); 
	}
	
	count_probes = 1;
	i=1;
	while(count_probes<probes){
		count_probes = count_edges(0, d, binary_string, cube_pos, i, count_probes, probes);
		i++;
	}
}
