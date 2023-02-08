#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

double* Input(FILE *fin, int *err, int *len)
{
	int i;
	double *arr = NULL;
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
				*err = -4; // No memory allocation
		}
		else
			*err = -3; // Not enough elements
	}
	else
		*err = -2; // Can't input the number of elements
	return arr;
}

void Qsort(double *arr, int first, int last)
{
	int left = first, right = last;
	double temp = 0, middle = arr[(first + last) / 2];
	do
	{
		while (arr[left] < middle)
			left++;
		while (arr[right] > middle)
			right--;
		if (left <= right)
		{
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
			left++;
			right--;
		}
	}
	while (left <= right);
	if (first < right)
		Qsort(arr, first, right);
	if (last > left)
		Qsort(arr, left, last);
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int i, err = 0, len = 0;
		double *arr;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			arr = Input(fin, &err, &len);
			if (err == 0)
			{
				Qsort(arr, 0, len - 1);
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