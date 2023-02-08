#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int pow(int k, int n)
{
	int res = 1;
	for (int i = 0; i < n; i++)
		res *= k;
	return res;
}

int in(FILE *fin, int *k, int *n, int *num, int **f)
{
	int err = 0, temp = 0;
	char *str = NULL;
	if (fscanf(fin, "%d %d ", k, n) == 2)
	{
		*num = pow(*k, *n);
		*f = (int*)calloc(*num, sizeof(int));
		str = (char*)calloc(*num + 1, sizeof(char));
		if ((*f != NULL) && (str != NULL))
		{
			if (fscanf(fin, "%s", str) != 0)
			{
				for (int i = 0; i < *num; i++)
				{
					temp = str[i] - '0';
					if (temp > 9)
						temp = str[i] - 'A' + 10;
					(*f)[i] = temp;
				}
			}
			else
				err = -3;
			free(str);
		}
		else
			err = -2;
	}
	else
		err = -1;
	return err;
}

int monotonicity(int *f, int k, int n, int num)
{
	int **set = NULL, len = 0, print = 0, count = 0;
	bool flag = false;
	len = num / k;
	set = (int**)calloc(num, sizeof(int*));
	if (set != NULL)
	{
		for (int i = 0; i < num; i++)
			set[i] = (int*)calloc(n, sizeof(int));
	}
	for (int i = 0; i < n; i++)
	{
		print = 0;
		count = 1;
		for (int j = 0; j < num; j++)
		{
			for (int s = j; s < len * count; s++)
				set[s][i] = print % k;
			print++;
			count++;
			j += (len - 1);
		}
		len /= k;
	}
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			flag = true;
			for (int s = 0; s < n; s++)
			{
				if (set[i][s] > set[j][s])
					flag = false;
			}
			if (flag == true)
			{
				if (f[i] > f[j])
				{
					for (int i = 0; i < num; i++)
						free(set[i]);
					free(set);
					return 0;
				}
			}
		}
	}
	for (int i = 0; i < num; i++)
		free(set[i]);
	free(set);
	return 1;
}

void out(FILE *fout, int mon)
{
	fprintf(fout, "%d", mon);
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int *f = NULL, err = 0, k = 0, n = 0, num = 0, mon = 0;
		FILE *fin, *fout;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			err = in(fin, &k, &n, &num, &f);
			if (err == 0)
			{
				mon = monotonicity(f, k, n, num);
				out(fout, mon);
			}
			free(f);
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}