#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning (disable: 4996)

int input(FILE *f_in, int **arr, int *len) {
	if (fscanf(f_in, "%d", len) != 1) return -1;
	if (*len <= 0) return -1;

	*arr = (int*)malloc(*len * sizeof(int));
	if (*arr == NULL) return -1;

	for (int i = 0; i < *len; i++) {
		if (fscanf(f_in, "%d", &(*arr)[i]) != 1) {
			free(*arr);
			return -1;
		}
	}

	return 0;
}

int counting_sort(int *arr, int len) {
	int min = arr[0], max = arr[0];

	for (int i = 0; i < len; i++) {
		if (arr[i] < min) min = arr[i];
		else if (arr[i] > max) max = arr[i];
	}

	int temp_len = max - min + 1;
	int *temp_arr = NULL;

	temp_arr = (int*)calloc(temp_len, sizeof(int));
	if (temp_arr == NULL) return -1;

	for (int i = 0; i < len; i++) temp_arr[arr[i] - min]++;

	for (int i = min, k = 0; i <= max; i++) {
		for (int j = 0; j < temp_arr[i - min]; j++, k++)
			arr[k] = i;
	}

	free(temp_arr);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int len = 0, err = 0;
	int *arr = NULL;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &arr, &len);
	if (err != 0) return -1;

	err = counting_sort(arr, len);
	if (err != 0) return -1;

	fprintf(f_out, "%d ", len);
	for (int i = 0; i < len; i++) fprintf(f_out, "%d ", arr[i]);

	free(arr);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
