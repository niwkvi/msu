#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

char* in(FILE *fin, int *err, int *n, int *num)
{
	char *conj = NULL, *str = NULL;
	*err = 0;
	if (fscanf(fin, "%d %d ", n, num) == 2)
	{
		conj = (char*)calloc((*n) * (*num), sizeof(char));
		str = (char*)calloc(*n + 1, sizeof(char));
		if ((conj != NULL) && (str != NULL))
		{
			for (int i = 0; i < *num; i++)
			{
				if (fscanf(fin, "%s", str) != 0)
				{
					for (int j = 0; j < *n; j++)
						*(conj + i * (*n) + j) = str[j];
				}
				else
					*err = -3;
			}
			free(str);
			str = NULL;
		}
		else
			*err = -2;
	}
	else
		*err = -1;
	return conj;
}

void blake2(char *conj, int n, int num)
{
	int strnum = num - 1;
	while (strnum != 0)
	{
		for (int i = 0; i < num; i++)
		{
			if (i != strnum)
			{
				for (int j = 0; j < n; j++)
				{
					if ((*(conj + strnum * n + j) != '*') && (*(conj + strnum * n + j) != '3'))
					{
						if (*(conj + strnum * n + j) != *(conj + i * n + j))
							break;
						if (j == n - 1)
						{
							for (int k = 0; k < n; k++)
								*(conj + i * n + k) = '3';
						}
					}
				}
			}
		}
		strnum--;
	}
}

void sort(char *conj, int n, int num)
{
	char *tempconj = NULL;
	tempconj = (char*)calloc(n, sizeof(char));
	if (tempconj != NULL)
	{
		for (int i = num - 2; i >= 0; i--)
		{
			for (int k = num - 1; k >= i + 1; k--)
			{
				if (*(conj + i * n + 1) != '3')
				{
					for (int j = n - 1; j >= 0; j--)
					{
						if (((*(conj + i * n + j) == '1') && (*(conj + k * n + j) == '0')) || 
							((*(conj + i * n + j) == '*') && (*(conj + k * n + j) == '0')) || 
							((*(conj + i * n + j) == '*') && (*(conj + k * n + j) == '1')))
						{
							for (int s = 0; s < n; s++)
							{
								tempconj[s] = *(conj + i * n + s);
								*(conj + i * n + s) = *(conj + k * n + s);
								*(conj + k * n + s) = tempconj[s];
							}
						}
					}
				}
			}
		}
		free(tempconj);
		tempconj = NULL;
	}
}

void out(FILE *fout, char *conj, int n, int num)
{
	int k = 0, tempnum = num;
	for (int i = 0; i < num; i++)
	{
		if (*(conj + i * n + 1) == '3')
			tempnum--;
	}
	fprintf(fout, "%d %d\n", n, tempnum);
	for (int i = 0; i < num; i++)
	{
		if (*(conj + i * n + 1) != '3')
		{
			for (int j = 0; j < n; j++)
				fprintf(fout, "%c", *(conj + i * n + j));
			if (i < num - 1)
				fprintf(fout, "\n");
		}
		else
			k++;
		if (k == num)
			fprintf(fout, "%d 0", n);
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int err = 0, n = 0, num = 0;
		char *conj = NULL;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			conj = in(fin, &err, &n, &num);
			if (err == 0)
			{
				blake2(conj, n, num);
				sort(conj, n, num);
				out(fout, conj, n, num);
			}
			free(conj);
			conj = NULL;
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}