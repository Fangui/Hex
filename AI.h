# include "tree.h"

double minimax(struct tree *tree, int depth, double alpha, double beta);

struct tree *getTuple(struct tree *tree);

struct vector *getFreePos(struct matrix *mat, int capacity);

