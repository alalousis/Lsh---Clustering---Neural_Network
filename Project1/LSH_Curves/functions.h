int count_curves(char *);
int count_points(char *, struct curve *);
void save_input(char *, struct curve *);
double euclidean(struct point, struct point);
double dtw(struct curve, struct curve);
struct dtw_cell *min_neighbour(struct dtw_cell *, struct dtw_cell *, struct dtw_cell *);
double count_d(struct curve *, int);
void snap(struct curve *, int ****, int **, int, int, int);
void concat_curve(struct vec **, struct curve *, int ****, int, int, int);
float average_dist(int, int, struct vec *);
int modulo_calc(int, int, int);
void factors(int, int, int, int *);
unsigned int concat(struct h_func *, int);
void hash(struct list_node **, int, int, int);
int query_knn(int, int, struct curve *, struct vec **, struct vec, int *, int);
void lsh_train(struct vec **, struct h_func **, struct list_node ***, int *, int, int, int, int, int, int, int);
int lsh_search(struct vec **, struct vec, struct curve *, struct h_func **, struct list_node ***, int *, int *, int, int, int, int, int, int, int);
void lsh(struct vec **, struct vec *, struct curve *, int, int, int, int, int, int, int *, int *);
void write_output(char[256], int, struct curve *, struct vec *, int *, int *, int *, int *);