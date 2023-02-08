#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

double* Input(FILE *fin, int *err, int *len)
{
	int i, k = 0, len1 = 0, len2 = 0;
	double *arr = NULL, *arr1 = NULL, *arr2 = NULL;
	if (fscanf(fin, "%d", &len1) == 1)
	{
		if (len1 > 0)
		{
			arr1 = (double*)malloc(len1 * sizeof(double));
			if (arr1 != NULL)
			{
				for (i = 0; i < len1; i++)
				{
					if (fscanf(fin, "%lf", &arr1[i]) != 1)
					{
						free(arr1);
						arr1 = NULL;
						*err = -5; // Can't input the element
						break;
					}
				}
				if (fscanf(fin, "%d", &len2) == 1)
				{
					if (len2 > 0)
					{
						arr2 = (double*)malloc(len2 * sizeof(double));
						if (arr2 != NULL)
						{
							for (i = 0; i < len2; i++)
							{
								if (fscanf(fin, "%lf", &arr2[i]) != 1)
								{
									free(arr2);
									arr2 = NULL;
									*err = -5; // Can't input the element
									break;
								}
							}
							*len = len1 + len2;
							arr = (double*)malloc((*len) * sizeof(double));
							for (i = 0; i < len1; i++, k++)
								arr[k] = arr1[i];
							for (i = 0; i < len2; i++, k++)
								arr[k] = arr2[i];
							free(arr1);
							arr1 = NULL;
							free(arr2);
							arr2 = NULL;
						}
						else
							*err = -4; // No memory allocation
					}
					else
						*err = -3; // Not enough elements
				}
				else
					*err = -2; // Can't input the number of elements
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

void Sorting(double *arr, int len)
{
	int i, j;
	double temp = 0;
	for (i = 0; i < len - 1; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
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
				Sorting(arr, len);
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