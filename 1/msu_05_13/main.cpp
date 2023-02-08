#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable: 4996)

int* Input(FILE *fin, int *err, int *len)
{
	int i, *arr = NULL;
	if (fscanf(fin, "%d", len) == 1)
	{
		if (*len > 0)
		{
			arr = (int*)malloc((*len) * sizeof(int));
			if (arr != NULL)
			{
				for (i = 0; i < *len; i++)
				{
					if (fscanf(fin, "%d", &arr[i]) != 1)
					{
						free(arr);
						arr = NULL;
						*err = -5; // Can't input the element
						break;
					}
				}
			}
			else
				*err = -4; // No memory allocation
		}
		else
			*err = -3; // Not enough elements
	}
	else
		*err = -2; // Can't input the number of elements
	return arr;
}

void Plus1(int len, int *arr, FILE *fout)
{
	int i = len - 1, *arr1 = NULL;
	arr1 = (int*)malloc(len * sizeof(int));
	memcpy(arr1, arr, len * sizeof(int));
	if (arr1[i] < 9)
		arr1[i]++;
	else
	{
		do
		{
			arr1[i] = 0;
			i--;
			arr1[i]++;
		}
		while ((arr1[i] > 9) && (i != 0));
	}
	fprintf(fout, "%d ", len);
	for (i = 0; i < len; i++)
		fprintf(fout, "%d ", arr1[i]);
	fprintf(fout, "\n");
	free(arr1);
	arr1 = NULL;
}

void Minus1(int len, int *arr, FILE *fout)
{
	int i = len - 1, *arr2 = NULL;
	arr2 = (int*)malloc(len * sizeof(int));
	memcpy(arr2, arr, len * sizeof(int));
	if (arr2[i] > 0)
		arr2[i]--;
	else
	{
		do
		{
			arr2[i] = 9;
			i--;
			arr2[i]--;
		}
		while ((arr2[i] < 0) && (i != 0));
	}
	fprintf(fout, "%d ", len);
	for (i = 0; i < len; i++)
		fprintf(fout, "%d ", arr2[i]);
	fprintf(fout, "\n");
	free(arr2);
	arr2 = NULL;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int err = 0, len = 0, *arr;
		FILE *fin, *fout;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			arr = Input(fin, &err, &len);
			if (err == 0)
			{
				Plus1(len, arr, fout);
				Minus1(len, arr, fout);
			}
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}