#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int Input(const char* sf, double** m, int* n)
{
  FILE* f;
  int i, err = 0;
  f = fopen(sf, "r");
  if (f != NULL)
  {
    if (fscanf(f, "%d", n) == 1)
    {
      *m = (double*)calloc(*n, sizeof(double));
      for (i = 0; i < *n; i++)
	  {
        if (fscanf(f, "%lf", &(*m)[i]) != 1)
		{
          free(*m);
          *m = NULL;
          err = -4;
          break;
        }
	  }
	}
    else
      err = -2;
    fclose(f);
  }
  else
    err = -1;
  return err;
}

void Neighbors(double** m, int n)
{
  double r = 0, l = 0;
  r = *m[0];
  for (int i = 1; i < n-1; i++)
  {
    if (i % 2 == 1)
    {
      l = *m[i];
      *m[i] = (r + *m[i + 1]) / 2;
    }
    else if (i % 2 == 0)
    {
      r = *m[i];
      *m[i] = (l + *m[i + 1]) / 2;
    }
  }
}

void Output(const char* sf, double* m, int n, int err)
{
  FILE* f;
  f = fopen(sf, "w");
  if (f != NULL)
  {
    if (err == 0)
    {
      fprintf(f, "%d", n);
      for (int i = 0; i < n; i++)
        fprintf(f, "%lf", m[i]);
    }
    else if (err = -1)
      fprintf(f, "File is absent");
    else if (err = -2)
      fprintf(f, "File is empty");
    else if (err = -3)
      fprintf(f, "Sequence not found");
    else if (err = -4)
      fprintf(f, "Can't input array");
    fclose(f);
  }
}

int main(int argc, char* argv[])
{
  int err = 0, n;
  double* m = NULL;
  if (argc == 3)
  {
    err = Input(argv[1], &m, &n);
    Neighbors(&m, n);
    Output(argv[2], m, n, err);
  }
  return 0;
}