# include "matrix.h"


int testpath(struct matrix *mat, struct matrix *cell, int i, 
             int j, int currentVisit, int player)
{
  if(i < 0 || j < 0 || i >= mat->cols || j >= mat->lines || player != 
  mat->data[i * mat->cols + j] || cell->data[i * mat->cols + j] == currentVisit)
    return 0;

  if((player == 1 && j == mat->cols - 1) || (player == 2 && i == mat->cols -1))
    return 1;

  return (testpath(mat, cell, i - 1, j, currentVisit, player) ||
          testpath(mat, cell, i + 1, j, currentVisit, player) ||
          testpath(mat, cell, i, j - 1, currentVisit, player) ||
          testpath(mat, cell, i, j + 1, currentVisit, player) ||
          testpath(mat, cell, i - 1, j + 1, currentVisit, player) ||
          testpath(mat, cell, i + 1, i - 1, currentVisit, player));
}

int is_Finished(struct matrix *mat, struct matrix *cell, int currentVisit)
{
  int i = 0;
  while(i < mat->cols && testpath(mat, cell, i, 0, currentVisit, 1) == 0)
    ++i;
  if(i < mat->cols)
    return 1;

  int j = 0;
  while(j < mat->lines && testpath(mat, cell, 0, j, currentVisit, 2) == 0)
    ++j;

  if(j < mat->lines)
    return 2;

  return 0;
}

int game(int lines, int cols)
{
  int player = 0, valid = 0, win = 0, currentVisit = 0;
  struct matrix *mat = malloc(sizeof(struct matrix));
  struct matrix *cell = malloc(sizeof(struct matrix));
  mat = newMat(mat, lines, cols);
  cell = newMat(cell, lines, cols);

  int cpt = mat->lines * mat->cols;
  printMat(mat);

  for(; cpt > 0; --cpt)
  {
    ++currentVisit;
    ++player;
    valid = 0;
    if(player == 3)
      player = 1;

    while(valid == 0)
    {
      printf("lines : ");
      scanf("%d", &lines);
      printf("cols : ");
      scanf("%d", &cols);
      if(lines >= mat->lines || cols >= mat->cols)
        printf("Position impossible\n");
      else if (mat->data[lines * mat->cols + cols] != 0)
        printf("Position occupé\n");
      else
        valid = 1;
    }

    if(valid)
    {
      mat->data[lines * mat->cols + cols] = player;
      cell->data[lines * mat->cols + cols] = currentVisit;
      printf("\n");
      printMat(mat);
      win = is_Finished(mat, cell, currentVisit);
      if(win != 0)
      {
        freeMat(mat);
        freeMat(cell);
        return player;
      }
    }
  }
  freeMat(mat);
  freeMat(cell);
  return win;
}


int main()
{
  int lines = 2, cols = lines;
  int win = game(lines, cols);
  if(win == 0)
    printf("FAIL CODE \n");
  else
    printf("Joueur %d win\n", win);

  return 0;
}
