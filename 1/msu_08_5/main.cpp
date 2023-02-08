#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int Bit(FILE *fin, int *err)
{
	int x, ans = -1;
	if (fscanf(fin, "%d", &x) == 1)
	{
		while (x != 0)
		{
			x = x >> 1;
			ans++;
		}
	}
	else
		*err = -1; // Can't input the number
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
		ans = Bit(fin, &err);
		if (err == 0)
			fprintf(fout, "%d", ans);
		fclose(fin);
		fclose(fout);
	}
	return 0;
}