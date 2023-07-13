#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int is_equal(FILE *f_in, int *ans) {
	double x = 0, y = 0;

	if (fscanf(f_in, "%lf", &x) != 1) return -1;

	y = x;
	do {
		if (x != y) {
			*ans = 0;
			break;
		}
	}
	while (fscanf(f_in, "%lf", &x) == 1);
	
	return 0;
}

int main(int argc, char *argv[]) {
	FILE *f_in, *f_out;
	int ans = 1, err = 0;

	if (argc != 3) return -1;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;
	
	err = is_equal(f_in, &ans);
	if (err != 0) return -1;

	fprintf(f_out, "%d", ans);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
