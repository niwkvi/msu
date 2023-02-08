#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning (disable: 4996)

struct Spoint
{
	double x, y;
};

struct Scircle
{
	double x, y, r;
};

typedef struct Spoint point;

typedef struct Scircle circle;

Spoint* Input(FILE *fin, int *err, int *num)
{
	int i;
	*err = 0;
	Spoint *point = NULL;
	if (fscanf(fin, "%d", num) == 1)
	{
		if (*num > 0)
		{
			point = (Spoint*)calloc(*num, sizeof(Spoint));
			if (point != NULL)
			{
				for (i = 0; i < *num; i++)
				{
					if (fscanf(fin, "%lf %lf", &point[i].x, &point[i].y) != 2)
					{
						free(point);
						point = NULL;
						*err = -5; // Can't input the point
						break;
					}
				}
			}
			else
				*err = -4; // No memory allocation
		}
		else
			*err = -3; // Not enough points
	}
	else
		*err = -2; // Can't input the number of elements
	return point;
}

void Mincircle(Spoint *point, int num, Scircle *circle)
{
	int i, j, k, d, tempcheck;
	double tempx = 0, tempy = 0, tempr = 0, tempd = 0, area = 0, z = 0;
	circle->x = 0;
	circle->y = 0;
	circle->r = -1;
	if (num == 1)
	{
		circle->r = 0;
		circle->x = point[0].x;
		circle->y = point[0].y;
	}
	else if (num == 2)
	{
		circle->r = sqrt ((point[0].x - point[1].x) * (point[0].x - point[1].x) + (point[0].y - point[1].y) * (point[0].y - point[1].y)) / 2;
		circle->x = (point[0].x + point[1].x) / 2;
		circle->y = (point[0].y + point[1].y) / 2;
	}
	else
	{
		for (i = 0; i < num - 1; i++)
		{
			for (j = i + 1; j < num; j++)
			{
				tempr = sqrt ((point[i].x - point[j].x) * (point[i].x - point[j].x) + (point[i].y - point[j].y) * (point[i].y - point[j].y)) / 2;
				tempx = (point[i].x + point[j].x) / 2;
				tempy = (point[i].y + point[j].y) / 2;
				tempcheck = 0;
				for (k = 0; k < num; k++)
				{
					tempd = sqrt ((tempx - point[k].x) * (tempx - point[k].x) + (tempy - point[k].y) * (tempy - point[k].y));
					if (tempd > tempr)
					{
						tempcheck = 1;
						break;
					}
				}
				if ((tempcheck == 0) && ((circle->r == -1) || (tempr < circle->r)))
				{
					circle->r = tempr;
					circle->x = tempx;
					circle->y = tempy;
				}
			}
		}
		for (i = 0; i < num - 2; i++)
		{
			for (j = i + 1; j < num - 1; j++)
			{
				for (k = j + 1; k < num; k++)
				{
					area = ((point[j].x - point[i].x) * (point[k].y - point[i].y) - (point[j].y - point[i].y) * (point[k].x - point[i].x)) / 2;
					(area < 0) ? area *= -1 : area;
					if (area != 0)
					{
						if (point[i].x == point[j].x)
						{
							tempy = (point[i].y + point[j].y) / 2;
							tempx = (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[k].y) / 2 + (point[j].y + point[k].y) / 2 - (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[i].y) / 2;
							tempr = sqrt ((point[i].x - tempx) * (point[i].x - tempx) + (point[i].y - tempy) * (point[i].y - tempy));
							tempcheck = 0;
						}
						else if (point[j].x == point[k].x)
						{
							tempy = (point[j].y + point[k].y) / 2;
							tempx = (point[k].y - point[i].y) / (point[k].x - point[i].x) * (point[i].y + point[k].y) / 2 + (point[i].y + point[k].y) / 2 - (point[k].y - point[i].y) / (point[k].x - point[i].x) * (point[j].y + point[k].y) / 2;
							tempr = sqrt ((point[i].x - tempx) * (point[i].x - tempx) + (point[i].y - tempy) * (point[i].y - tempy));
							tempcheck = 0;
						}
						else if (point[i].x == point[k].x)
						{
							tempx = (point[i].y + point[j].y) / 2;
							tempy = (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[k].y) / 2 + (point[j].y + point[k].y) / 2 - (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[i].y) / 2;
							tempr = sqrt ((point[i].x - tempx) * (point[i].x - tempx) + (point[i].y - tempy) * (point[i].y - tempy));
							tempcheck = 0;
						}
						else
						{
											
							tempy = ((point[j].x * point[j].x + point[j].y * point[j].y - point[i].x * point[i].x - point[i].y * point[i].y) * (point[k].x - point[i].x) - (point[k].x * point[k].x + point[k].y * point[k].y - point[i].x * point[i].x - point[i].y * point[i].y) * (point[j].x - point[i].x)) / (2 * ((point[i].y - point[k].y) * (point[j].x - point[i].x) - (point[i].y - point[j].y) * (point[k].x - point[i].x)));
							tempx = (point[j].x * point[j].x + point[j].y * point[j].y - point[i].x * point[i].x - point[i].y * point[i].y + (2 * point[i].y - 2 * point[j].y) * tempy) / (2 * point[j].x - 2 * point[i].x);
							tempr = sqrt ((point[i].x - tempx) * (point[i].x - tempx) + (point[i].y - tempy) * (point[i].y - tempy));
							tempcheck = 0;
						}
					}
					else
						break;
					for (d = 0; d < num; d++)
					{
						tempd = sqrt ((tempx - point[d].x) * (tempx - point[d].x) + (tempy - point[d].y) * (tempy - point[d].y));
						if (tempd > tempr)
						{
							tempcheck = 1;
							break;
						}
					}
					if ((tempcheck == 0) && ((circle->r == -1) || (tempr < circle->r)))
					{
						circle->r = tempr;
						circle->x = tempx;
						circle->y = tempy;
					}
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int num, err = 0;
		Spoint *point = NULL;
		Scircle *circle = NULL;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			point = Input(fin, &err, &num);
			if (err == 0)
			{
				circle = (Scircle*)calloc(1, sizeof(Scircle));
				Mincircle(point, num, circle);
				fprintf(fout, "%lf %lf %lf", circle->x, circle->y, circle->r);
			}
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}