#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int input(FILE *f_in, int *x) {
	if (fscanf(f_in, "%d", x) != 1) return -1;
	return 0;
}

int find_pos(int x, int *pos) {
	*pos = -1;
	
	while (x != 0) {
		x = x >> 1;
		(*pos)++;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int x = 0, pos = 0, err = 0;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &x);
	if (err != 0) return -1;

	find_pos(x, &pos);

	fprintf(f_out, "%d", pos);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
