# include "AI.h"

double minimax(struct tree *tree, int depth, double alpha, double beta)
{
  if(tree->nbChildren == 0)
    return tree->value;

  double curr = minimax(tree->children[0], depth + 1, alpha, beta);
  double Child;
  tree->value = curr;
  if(depth % 2 == 0)
  {
    for(int i = 1; i < tree->nbChildren; ++i)
    {
      Child = minimax(tree->children[i], depth + 1, alpha, beta);
      if(curr < Child)
      {
        curr = Child;
        tree->value = curr;
      }
      if(curr > beta)
      {
        for(int j = i; j < tree->nbChildren; ++j)
          freeTree(tree->children[j]);
        tree->nbChildren = i;
      }
      if(alpha < curr)
        alpha = curr;
    }
  }

  else
  {
    for(int i = 1; i < tree->nbChildren; ++i)
    {
      Child = minimax(tree->children[i], depth + 1, alpha, beta);
      if(curr > Child)
      {
        curr = Child;
        tree->value = curr;
      }
      if(alpha >= curr)
      {
        for(int j = i; j < tree->nbChildren; ++j)
          freeTree(tree->children[j]);
        tree->nbChildren = i;
        return curr;
      }

      if(beta > curr)
        beta = curr;
    }
  }
  return curr;
}

struct vector *getFreePos(struct matrix *mat, int capacity)
{
  struct vector *freePos = vector_make(capacity);
  for(int i = 0; i < mat->lines; ++i)
  {
    for(int j = 0; j < mat->cols; ++j)
    {
      if(mat->data[i * mat->cols + j] == 0)
      {
        struct Tuple *Tuple = malloc(sizeof(struct Tuple));
        Tuple->t1 = i;
        Tuple->t2 = j;
        vector_push_back(freePos, Tuple);
      }
    }
  }
  return freePos;
}

struct tree *getTuple(struct tree *tree)
{
  if(tree->nbChildren == 0)
    return tree;
  struct tree *curr = tree->children[0];

  for(int i = 1; i < tree->nbChildren; ++i)
    if(curr->value < tree->children[i]->value)
      curr = tree->children[i];

  return curr;
}

