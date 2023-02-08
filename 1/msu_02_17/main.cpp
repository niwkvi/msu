#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int Sequence(FILE *fin, int *err)
{
	int len = 0, templen = 0;
	double x, cur = 0;
	if (fscanf(fin, "%lf", &x) == 1)
	{
		cur = x;
		do
		{
			if (x == cur)
				templen++;
			else if (templen > len)
			{
				len = templen;
				templen = 1;
				cur = x;
			}
			else
			{
				cur = x;
				templen = 1;
			}
		}
		while (fscanf(fin, "%lf", &x) == 1);
		if (templen > len)
			len = templen;
	}
	else
		*err = -1; // Can't input the element
	return len;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int err = 0, len = 0;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			len = Sequence(fin, &err);
			if (err == 0)
				fprintf(fout, "%d", len);
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}