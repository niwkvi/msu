#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
			*err = -3; // Not enough points
	}
	else
		*err = -2; // Can't input the number of elements
	return arr;
}

void Countingsort(int *arr, int len)
{
	int i, j, k = 0, min = arr[0], max = arr[0];
	for (i = 0; i < len; i++)
	{
		if (arr[i] < min)
			min = arr[i];
		else if (arr[i] > max)
			max = arr[i];
	}
	int *arr2, len2 = max - min + 1;
	arr2 = (int*)malloc(len2 * sizeof(int));
	for (i = 0; i < len2; i++)
		arr2[i] = 0;
	for (i = 0; i < len; i++)
		arr2[arr[i] - min]++;
	for (i = min; i <= max; i++)
	{
		for (j = 0; j < arr2[i - min]; j++)
			arr[k++] = i;
	}
	free(arr2);
	arr2 = NULL;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int i, err = 0, len = 0, *arr;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			arr = Input(fin, &err, &len);
			if (err == 0)
			{
				Countingsort(arr, len);
				fprintf(fout, "%d ", len);
				for (i = 0; i < len; i++)
					fprintf(fout, "%d ", arr[i]);
			}
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}