# ifndef MATRIX_H_
# define MATRIX_H_

# include <stdio.h>
# include <stdlib.h>

struct matrix
{
  int *data;
  int lines;
  int cols;
};

struct matrix *newMat(struct matrix *mat, int lines, int cols);

struct matrix *cloneMat(struct matrix *mat);

void freeMat(struct matrix *mat);

void printMat(struct matrix *mat);


# endif
