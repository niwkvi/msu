#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning (disable: 4996)

typedef struct Point {
	double x, y;
} Point;

int input(FILE *f_in, Point **point, int *num) {
	if (fscanf(f_in, "%d", num) != 1) return -1;
	if (*num <= 2) return -1;

	*point = (Point*)calloc(*num, sizeof(Point));
	if (*point == NULL) return -1;

	for (int i = 0; i < *num; i++) {
		if (fscanf(f_in, "%lf %lf", &(*point)[i].x, &(*point)[i].y) != 2) {
			free(*point);
			return -1;
		}
	}

	return 0;
}

int find_cross_prod(Point p1, Point p2, Point p3) {
	return ((p3.x - p2.x) * (p1.y - p2.y)) - ((p3.y - p2.y) * (p1.x - p2.x));
}

int is_convex(Point *point, int num) {
	int ans = 1, check1  = 0, check2 = 0;
	double cross_prod = 0;

	for (int i = 0; i < num; i++) {
		int j = (i + 1) % num;
		int k = (i + 2) % num;

		cross_prod = find_cross_prod(point[i], point[j], point[k]);

		if (cross_prod < 0) check1 = 1;
		else if (cross_prod > 0) check2 = 1;
		
		if ((check1 == 1) && (check2 == 1)) ans = 0;
	}

	return ans;
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int num = 0, ans = 0, err = 0;
	Point *point = NULL;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &point, &num);
	if (err != 0) return -1;

	ans = is_convex(point, num);

	fprintf(f_out, "%d", ans);

	free(point);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
