#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int Sequence(FILE *fin, int *err)
{
	int ans = 0;
	double x, y = 0;
	*err = 0;
	if (fscanf(fin, "%lf", &x) == 1)
	{
		y = x;
		do
		{
			ans = 1;
			if (x != y)
			{
				ans = 0;
				break;
			}
		}
		while (fscanf(fin, "%lf", &x) == 1);
	}
	else
		*err = -1; // Can't input the element
	return ans;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int err = 0, ans = 0;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			ans = Sequence(fin, &err);
			if (err == 0)
				fprintf(fout, "%d", ans);
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}