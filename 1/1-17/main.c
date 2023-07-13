#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int find_max_len(FILE *f_in, int *max_len) {
	int len = 0;
	double x = 0, cur_x = 0;

	if (fscanf(f_in, "%lf", &x) != 1) {
		return -1;
	}

	cur_x = x;
	do {
		if (x == cur_x) len++;
		else if (len > *max_len) {
			*max_len = len;
			len = 1;
			cur_x = x;
		}
		else {
			len = 1;
			cur_x = x;
		}
	}
	while (fscanf(f_in, "%lf", &x) == 1);

	if (len > *max_len) {
		*max_len = len;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	FILE *f_in, *f_out;
	int max_len = 0, err = 0;

	if (argc != 3) return -1;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;
	
	err = find_max_len(f_in, &max_len);
	if (err != 0) return -1;

	fprintf(f_out, "%d", max_len);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
