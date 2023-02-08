#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

void bubblesort(double *arr, int len)
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
		int len = 0, i;
		double *arr;
		FILE *fin, *fout;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			if (fscanf(fin, "%d", &len) == 1)
			{
				if (len > 0)
				{
					arr = (double*)malloc(len * sizeof(double));
					if (arr != NULL)
					{
						for (i = 0; i < len; i++)
						{
							if (fscanf(fin, "%lf", &arr[i]) != 1)
							{
								free(arr);
								arr = NULL;
								break;
							}
						}
						bubblesort(arr, len);
						fprintf(fout, "%d ", len);
						for (i = 0; i < len; i++)
							fprintf(fout, "%lf ", arr[i]);
						fclose(fin);
						fclose(fout);
					}
					else
					{
						fclose(fin);
						fclose(fout);
						return 0;
					}
				}
				else
				{
					fclose(fin);
					fclose(fout);
					return 0;
				}
			}
			else
			{
				fclose(fin);
				fclose(fout);
				return 0;
			}
		}
	}
	return 0;
}