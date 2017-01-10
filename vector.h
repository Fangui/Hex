# ifndef VECTOR_H
# define VECTOR_H

# include "matrix.h"

struct Tuple
{
  int t1, t2;
};

struct vector
{
  int capacity, size;
  struct Tuple **data;
};

void print_vect(struct vector *vect);

struct vector *vector_make(int capacity);

void vector_push_back(struct vector *vect, struct Tuple *x);

void vector_extract_at(struct vector *vect, int pos);

void freeVect(struct vector *vect);


# endif
