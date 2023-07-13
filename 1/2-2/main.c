#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

#define SWAP(a, b, c) {(c) = (a); (a) = (b); (b) = (c);}

int input_arr(FILE *f_in, double **arr, int *len) {
	if (fscanf(f_in, "%d", len) != 1) return -1;
	if (*len <= 0) return -1;

	*arr = (double*)malloc(*len * sizeof(double));
	if (arr == NULL) return -1;

	for (int i = 0; i < *len; i++) {
		if (fscanf(f_in, "%lf", &(*arr)[i]) != 1) {
			free(*arr);
			return -1;
		}
	}

	return 0;
}

void reverse_arr(double *arr, int len) {
	double temp = 0;
	for (int i = 0; i < len / 2; i++) SWAP(arr[i], arr[len - i - 1], temp);
}

int main(int argc, char *argv[]) {
	FILE *f_in, *f_out;
	int len = 0, err = 0;
	double *arr = NULL;

	if (argc != 3) return -1;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input_arr(f_in, &arr, &len);
	if (err != 0) return -1;

	reverse_arr(arr, len);

	fprintf(f_out, "%d ", len);
	for (int i = 0; i < len; i++) fprintf(f_out, "%lf ", arr[i]);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
