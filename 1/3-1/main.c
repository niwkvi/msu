#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int input(FILE *f_in, int *x, int *n) {
	if (fscanf(f_in, "%d", x) != 1) return -1;
	if (fscanf(f_in, "%d", n) != 1) return -1;
	return 0;
}

void power(int x, int n, double *ans) {
	int is_neg = 0;
	*ans = 1;
	
	if (n < 0) {
		is_neg = 1;
		n *= -1;
	}

	while (n) {
		if (n & 1) {
			(*ans) *= x;
			n--;
		}
		x *= x;
		n >>= 1;
	}

	if (is_neg) *ans = 1 / * ans;
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int x = 0, n = 0, err = 0;
	double ans = 0;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &x, &n);
	if (err != 0) return -1;

	power(x, n, &ans);

	fprintf(f_out, "%lf", ans);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
