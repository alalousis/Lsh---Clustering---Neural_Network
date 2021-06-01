struct vec{
	char id[64];
	double *coord;
	char isMedoid;
	int nearest;
	int second_nearest;
};

struct h_func{
	int h_sum;
	int *s;
};

struct list_node{
	unsigned int g;
	int vec_pos;
	struct list_node *next;
};

