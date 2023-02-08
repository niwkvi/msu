#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int Sequence(FILE *fin, int *err)
{
	int sum = 0;
	double x, min = 0;
	*err = 0;
	if (fscanf(fin, "%lf", &x) == 1)
	{
		min = x;
		do
		{
			if (x < min)
			{
				min = x;
				sum = 1;
			}
			else if (x == min)
				sum++;
		}
		while (fscanf(fin, "%lf", &x) == 1);
	}
	else
		*err = -1; //Can't input the element
	return sum;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int err = 0, sum = 0;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			sum = Sequence(fin, &err);
			if (err == 0)
				fprintf(fout, "%d", sum);
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}