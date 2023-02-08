#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

void stupidsort(double *arr, int len)
{
	int i = 0;
	double temp = 0;
	while (i < len - 1)
	{
		if (arr[i + 1] < arr[i])
		{
			temp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = temp;
			i = 0;
		}
		else
			i++;
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
						stupidsort(arr, len);
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