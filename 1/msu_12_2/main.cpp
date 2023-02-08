#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning (disable: 4996)

struct Spoint
{
	double x, y;
};

typedef struct Spoint point;

Spoint* Input(FILE *fin, int *err, int *num)
{
	int i;
	*err = 0;
	Spoint *point = NULL;
	if (fscanf(fin, "%d", num) == 1)
	{
		if (*num > 2)
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
			*err = -3; // Not enough points (polygons must have at least 3 points)
	}
	else
		*err = -2; // Can't input the number of elements
	return point;
}

int Convpol(Spoint *point, int num)
{
	int ans = 1, i, j = 0, k = 0, check1 = 0, check2 = 0;
	double crossproduct = 0;
	for (i = 0; i < num; i++)
	{
		j = (i + 1) % num;
		k = (i + 2) % num;
		crossproduct = ((point[k].x - point[j].x) * (point[i].y - point[j].y)) - ((point[k].y - point[j].y) * (point[i].x - point[j].x));
		if (crossproduct < 0)
			check1 = 1;
		else if (crossproduct > 0)
			check2 = 1;
		if ((check1 == 1) && (check2 == 1))
			ans = 0;
	}
	return ans;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int num, err = 0, ans = 0;
		Spoint *point = NULL;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			point = Input(fin, &err, &num);
			if (err == 0)
			{
				ans = Convpol(point, num);
				fprintf(fout, "%d", ans);
			}
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}