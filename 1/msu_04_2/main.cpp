#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

#define SWAP(a, b, c) {(c) = (a); (a) = (b); (b) = (c);}

double* Input(FILE *fin, int *err, int *len)
{
	int i;
	double *arr = NULL;
	*err = 0;
	if (fscanf(fin, "%d", len) == 1)
	{
		if (*len > 0)
		{
			arr = (double*)malloc((*len) * sizeof(double));
			if (arr != NULL)
			{
				for (i = 0; i < *len; i++)
				{
					if (fscanf(fin, "%lf", &arr[i]) != 1)
					{
						free(arr);
						arr = NULL;
						*err = -5; // Can't input the element
						break;
					}
				}
			}
			else
				*err = 4; // No memory allocation
		}
		else
			*err = -3; // Not enough elements
	}
	else
		*err = -2; // Can't input the number of elements
	return arr;
}

void Arrayrev(double *arr, int len)
{
	int i;
	double c = 0;
	for (i = 0; i < len / 2; i++)
		SWAP(arr[i], arr[len - i - 1], c);
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int i, err = 0, len;
		double *arr;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			arr = Input(fin, &err, &len);
			if (err == 0)
			{
				Arrayrev(arr, len);
				fprintf(fout, "%d ", len);
				for (i = 0; i < len; i++)
					fprintf(fout, "%lf ", arr[i]);
			}
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}