struct vec{
	char id[64];
	//int id;
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

struct curve{
	int id;
	int noPoints;
	char isMedoid;
	int nearest;
	int second_nearest;
	struct point *points;
};

struct point{
	double x;
	double y;
};

struct dtw_cell{
	double value;
	struct dtw_cell *previous;
	int x;
	int y;
};

struct pair{
	int one;
	int two;
};

