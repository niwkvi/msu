#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

#define SWAP(a, b, c) {(c) = (a); (a) = (b); (b) = (c);}

int input_arr(FILE *f_in, double **arr, int *len) {
	int len1 = 0, len2 = 0;
	double *arr1 = NULL, *arr2 = NULL;

	if (fscanf(f_in, "%d", &len1) != 1) return -1;
	if (len1 <= 0) return -1;

	arr1 = (double*)malloc(len1 * sizeof(double));
	if (arr1 == NULL) return -1;
	
	for (int i = 0; i < len1; i++) {
		if (fscanf(f_in, "%lf", &arr1[i]) != 1) {
			free(arr1);
			return -1;
		}
	}
	
	if (fscanf(f_in, "%d", &len2) != 1) return -1;
	if (len2 <= 0) return -1;

	arr2 = (double*)malloc(len2 * sizeof(double));
	if (arr2 == NULL) return -1;
	
	for (int i = 0; i < len2; i++) {
		if (fscanf(f_in, "%lf", &arr2[i]) != 1) {
			free(arr2);
			return -1;
		}
	}
	
	*len = len1 + len2;

	*arr = (double*)malloc(*len * sizeof(double));

	for (int i = 0; i < len1; i++) {

		*arr[i] = arr1[i];
	}
	
	for (int i = 0, j = len1; i < len2, j < len2; i++, j++)
		*arr[j] = arr2[i];
	
	free(arr1);
	free(arr2);
	
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
	FILE *f_in, *f_out;
	int len = 0, err = 0;
	double *arr = NULL;

	//if (argc != 3) return -1;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input_arr(f_in, &arr, &len);
	if (err != 0) return -1;

	sort(arr, len);

	fprintf(f_out, "%d ", len);
	for (int i = 0; i < len; i++) fprintf(f_out, "%lf ", arr[i]);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
