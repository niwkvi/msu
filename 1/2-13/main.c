#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int print(FILE *f_out, int *arr, int len) {
	fprintf(f_out, "%d ", len);
	for (int i = 0; i < len; i++) fprintf(f_out, "%d ", arr[i]);
	fprintf(f_out, "\n");
	return 0;
}

int plus_1(FILE *f_out, int *arr, int len) {
	int pos = len - 1;
	int *temp_arr = NULL;

	temp_arr = (int*)malloc(len * sizeof(int));
	if (temp_arr == NULL) return -1;

	memcpy(temp_arr, arr, len * sizeof(int));

	if (temp_arr[pos] < 9) temp_arr[pos]++;
	else {
		do {
			temp_arr[pos] = 0;
			pos--;
			temp_arr[pos]++;
		}
		while ((temp_arr[pos] > 9) && (pos != 0));
	}

	print(f_out, temp_arr, len);

	free(temp_arr);

	return 0;
}

int minus_1(FILE *f_out, int *arr, int len) {
	int pos = len - 1;
	int *temp_arr = NULL;

	temp_arr = (int*)malloc(len * sizeof(int));
	if (temp_arr == NULL) return -1;

	memcpy(temp_arr, arr, len * sizeof(int));

	if (temp_arr[pos] > 0) temp_arr[pos]--;
	else {
		do {
			temp_arr[pos] = 9;
			pos--;
			temp_arr[pos]--;
		} while ((temp_arr[pos] < 0) && (pos != 0));
	}
	
	print(f_out, temp_arr, len);

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

	err = plus_1(f_out, arr, len);
	if (err != 0) return -1;

	err = minus_1(f_out, arr, len);
	if (err != 0) return -1;

	free(arr);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
