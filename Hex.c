# include <time.h>
# include "AI.h"


int testpath(struct matrix *mat, struct matrix *cell, int i, 
             int j, int currentVisit, int player)
{
  if(i < 0 || j < 0 || i >= mat->cols || j >= mat->lines || player != 
  mat->data[j * mat->cols + i] || cell->data[j * mat->cols + i] == currentVisit)
    return 0;
  cell->data[j * mat->cols + i] = currentVisit;

  if((player == 1 && j == mat->lines - 1) || (player == 2 && i == mat->cols -1))
    return 1;

  return (testpath(mat, cell, i - 1, j, currentVisit, player) ||
          testpath(mat, cell, i + 1, j, currentVisit, player) ||
          testpath(mat, cell, i, j - 1, currentVisit, player) ||
          testpath(mat, cell, i, j + 1, currentVisit, player) ||
          testpath(mat, cell, i - 1, j + 1, currentVisit, player) ||
          testpath(mat, cell, i + 1, j - 1, currentVisit, player));
}

int is_Finished(struct matrix *mat, struct matrix *cell, 
                int currentVisit, int player)
{
  int i = 0;
  if(player == 1)
  {
    while(i < mat->cols && testpath(mat, cell, i, 0, currentVisit, 1) == 0)
      ++i;
    if(i < mat->cols)
      return 1;
  }
  else
  {
    int j = 0;
    while(j < mat->lines && testpath(mat, cell, 0, j, currentVisit, 2) == 0)
      ++j;
    if(j < mat->lines)
      return 2;
  }
  return 0;
}

double MonteCarlo(struct matrix *mat, struct matrix *Cell,
                  int cpt, int currentVisit, int player, double max_game)
{
  double game_win = 0;

  for(int i = 0; i < max_game; ++i)
  {
    struct vector *freePos = getFreePos(mat, cpt);
    struct matrix *cell = cloneMat(Cell);
    int curr = currentVisit;
    srand(time(NULL));
    while(freePos->size > 0)
    {
      if(player == 3)
        player = 1;
  
      int r = rand() % freePos->size;
//      printf("r value :%d\n",r);
//      print_vect(freePos);
      mat->data[freePos->data[r]->t1 * mat->cols + freePos->data[r]->t2] = player;
      ++curr;
      if(is_Finished(mat, cell, curr, player))
      {
        if(player == 2)
          ++game_win;
        else
          freePos->size = 0;
      }
      ++player;
      vector_extract_at(freePos, r);
    }
    freeVect(freePos);
    freeMat(cell);
  }
  return game_win / max_game;
}

void treeScore(struct tree *tree, struct matrix *mat, struct matrix *Cell, int
currentVisit, int player, int cpt, int max_game, int depth, int max_depth)
{
  if(depth >= max_depth)
  {
    tree->nbChildren = 0;
    tree->value = MonteCarlo(mat, Cell, cpt, currentVisit, player, max_game);
    return;
  }

  if(player == 3)
    player = 1;

   struct vector *freePos = getFreePos(mat, cpt);

   addChildren(tree, freePos);

   for(int i = 0; i < tree->nbChildren; ++i)
   {
     struct matrix *clone = cloneMat(mat);
     struct matrix *cell = cloneMat(Cell);

     clone->data[tree->children[i]->t1 * clone->cols + tree->children[i]->t2] = player;
     if( is_Finished(mat, cell, currentVisit, player) )
     {
       if(player == 1)
         tree->children[i]->value = -1;
       else
         tree->children[i]->value = 1;
       tree->children[i]->nbChildren = 0;
     }
     else
     {
       treeScore(tree->children[i], clone, cell, currentVisit + 1, player + 1,
                 cpt - 1, max_game, depth + 1, max_depth);
     }
     freeMat(cell);
     freeMat(clone);
   }
  freeVect(freePos);
}

int game(int lines, int cols, int max_game)
{
  int player = 0, valid = 0, win = 0, currentVisit = 0;
  printf("Player first?(1 or 2) : ");
  scanf("%d", &player);

  int max_depth = 3; //

  struct matrix *mat = malloc(sizeof(struct matrix));
  struct matrix *cell = malloc(sizeof(struct matrix));
  mat = newMat(mat, lines, cols);
  cell = newMat(cell, lines, cols);

  int cpt = mat->lines * mat->cols;

  if(player == 2)
  {
    --cpt;
    ++currentVisit;
    int mid = mat->lines / 2 * mat->cols + mat->cols / 2;
    mat->data[mid] = 2;
    cell->data[mid] = currentVisit;
  }
  else
    player = 0;

  printMat(mat);

  for(; cpt > 0; --cpt)
  {
    ++currentVisit;
    ++player;
    valid = 0;
    if(player == 3)
      player = 1;

    if(player == 1)
    {
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
    }
    else
    {
      struct tree *tree = malloc(sizeof(struct tree));
      tree->value = 0;

      treeScore(tree, mat, cell, currentVisit, player, cpt, max_game, 0, max_depth);

      minimax(tree, 0, -150, 150);
      struct tree *treePos = getTuple(tree);

      lines = treePos->t1;
      cols = treePos->t2;

      freeTree(tree);
    }

    mat->data[lines * mat->cols + cols] = player;
    printf("\n");
    printMat(mat);
    win = is_Finished(mat, cell, currentVisit, player);
    if(win != 0)
    {
      freeMat(mat);
      freeMat(cell);
      return player;
    }
  }
  freeMat(mat);
  freeMat(cell);
  return win;
}


int main()
{
  int lines = 4, cols = lines;
  int max_game = 200;
  int win = game(lines, cols, max_game);
  if(win == 0)
    printf("FAIL CODE \n");
  else
    printf("Joueur %d win\n", win);

  return 0;
}
