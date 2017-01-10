# include "vector.h"

void print_vect(struct vector *vect)
{
  for(int i = 0; i < vect->size; ++i)
    printf("T1 : %d | T2 : %d\n", vect->data[i]->t1, vect->data[i]->t2);

}
struct vector *vector_make(int capacity)
{
  struct vector *vect = malloc(sizeof(struct vector));
  vect->capacity = capacity;
  vect->size = 0;
  vect->data = malloc(sizeof(struct Tuple) * capacity);
  return vect;
}

void vector_push_back(struct vector *vect, struct Tuple *x)
{
  vect->data[vect->size] = x;
  ++(vect->size);
}

void vector_extract_at(struct vector *vect, int pos)
{
  if(vect->size == 0 || pos >= vect->size)
    return;

  for(; pos < vect->size; ++pos)
    vect->data[pos] = vect->data[pos + 1];

  --(vect->size);
}

void freeVect(struct vector *vect)
{
  for(int i = 0; i < vect->size; ++i)
    free(vect->data[i]);
  free(vect->data);
  free(vect);
}
