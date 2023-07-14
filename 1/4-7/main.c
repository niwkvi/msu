#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

#define SWAP(a, b, c) {(c) = (a); (a) = (b); (b) = (c);}

int input(FILE *f_in, double **arr, int *len) {
	if (fscanf(f_in, "%d", len) != 1) return -1;
	if (*len <= 0) return -1;

	*arr = (double*)malloc(*len * sizeof(double));
	if (*arr == NULL) return -1;

	for (int i = 0; i < *len; i++) {
		if (fscanf(f_in, "%lf", &(*arr)[i]) != 1) {
			free(*arr);
			return -1;
		}
	}

	return 0;
}

void q_sort(double *arr, int first, int last) {
	int left = first, right = last;
	double temp = 0, middle = arr[(first + last) / 2];

	do {
		while (arr[left] < middle) left++;
		while (arr[right] > middle) right--;
		if (left <= right) {
			SWAP(arr[left], arr[right], temp);
			left++;
			right--;
		}
	}
	while (left <= right);

	if (first < right) q_sort(arr, first, right);
	if (last > left) q_sort(arr, left, last);
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

	q_sort(arr, 0, len - 1);

	fprintf(f_out, "%d ", len);
	for (int i = 0; i < len; i++) fprintf(f_out, "%lf ", arr[i]);

	free(arr);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
