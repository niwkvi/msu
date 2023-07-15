#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

#define SWAP(a, b, c) {(c) = (a); (a) = (b); (b) = (c);}

int input(FILE *f_in, double **arr, int *len) {
	int len_1 = 0, len_2 = 0;
	double *arr_1 = NULL, *arr_2 = NULL;

	if (fscanf(f_in, "%d", &len_1) != 1) return -1;
	if (len_1 <= 0) return -1;

	arr_1 = (double*)malloc(len_1 * sizeof(double));
	if (arr_1 == NULL) return -1;
	
	for (int i = 0; i < len_1; i++) {
		if (fscanf(f_in, "%lf", &arr_1[i]) != 1) {
			free(arr_1);
			return -1;
		}
	}
	
	if (fscanf(f_in, "%d", &len_2) != 1) return -1;
	if (len_2 <= 0) return -1;

	arr_2 = (double*)malloc(len_2 * sizeof(double));
	if (arr_2 == NULL) return -1;
	
	for (int i = 0; i < len_2; i++) {
		if (fscanf(f_in, "%lf", &arr_2[i]) != 1) {
			free(arr_2);
			return -1;
		}
	}
	
	*len = len_1 + len_2;

	*arr = (double*)malloc(*len * sizeof(double));
	if (*arr == NULL) return -1;

	for (int i = 0; i < len_1; i++) (*arr)[i] = arr_1[i];
	
	for (int i = 0, j = len_1; i < len_2; i++, j++) (*arr)[j] = arr_2[i];
	
	free(arr_1);
	free(arr_2);
	
	return 0;
}

void sort(double *arr, int len) {
	double temp = 0;
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (arr[i] > arr[j]) SWAP(arr[i], arr[j], temp);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int len = 0, err = 0;
	double *arr = NULL;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &arr, &len);
	if (err != 0) return -1;

	sort(arr, len);

	fprintf(f_out, "%d ", len);
	for (int i = 0; i < len; i++) fprintf(f_out, "%lf ", arr[i]);

	free(arr);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
