#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int count_min_values(FILE *f_in, int *count) {
	double x = 0, min_x = 0;

	if (fscanf(f_in, "%lf", &x) != 1) return -1;

	min_x = x;
	do {
		if (x < min_x) {
			min_x = x;
			*count = 1;
		}
		else if (x == min_x) (*count)++;
	}
	while (fscanf(f_in, "%lf", &x) == 1);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;
	
	FILE *f_in, *f_out;
	int count = 0, err = 0;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;
	
	err = count_min_values(f_in, &count);
	if (err != 0) return -1;

	fprintf(f_out, "%d", count);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
