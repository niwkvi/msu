#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning (disable: 4996)

struct Point
{
  double x, y;
};

typedef struct Point point;

struct Section
{
  Point b, e;
};

typedef struct Section sec;

void Input(Section* sec)
{
  FILE* read;
  read = fopen("Input.txt", "r");
  if (read != NULL)
  {
    fscanf(read, "%lf %lf %lf %lf", &(*sec).b.x, &(*sec).b.y, &(*sec).e.x, &(*sec).e.y);
  }
  fclose(read);
}

void Solve(Section* sec)
{
  FILE* write;
  write = fopen("Output.txt", "w");
  fprintf(write, "%lf %lf %lf %lf", &(*sec).b.x, &(*sec).b.y, &(*sec).e.x, &(*sec).e.y);
  fclose(write);
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		Section *sec = NULL;
		Input(sec);
		Solve(sec);
	}
	return 0;
}