#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int Power(FILE *fin, int *err)
{
	int x, n, ans = 1;
	if (fscanf(fin, "%d", &x) == 1)
	{
		if (fscanf(fin, "%d", &n) == 1)
		{
			while (n)
			{
				if (n & 1)
				{
					ans *= x;
					n--;
				}
				x *= x;
				n >>= 1;
			}
		}
		else
			*err = -2; // Can't input the power
	}
	else
		*err = -1; // Can't input the base
	return ans;
}

int main(int argc, char *argv[])
{
	FILE *fin, *fout;
	int ans = 0, err = 0;
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	if ((fin != NULL) && (fout != NULL))
	{
		ans = Power(fin, &err);
		if (err == 0)
			fprintf(fout, "%d", ans);
		fclose(fin);
		fclose(fout);
	}
	return 0;
}