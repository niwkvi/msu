#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning (disable: 4996)

typedef struct Point {
	double x, y;
} Point;

typedef struct Circle {
	double x, y, r;
} Circle;

int input(FILE *f_in, Point **point, int *num) {
	if (fscanf(f_in, "%d", num) != 1) return -1;
	if (*num <= 0) return -1;

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

void find_min_circle(Point *point, Circle *circle, int num) {
	int check = 0;
	double temp_x = 0, temp_y = 0, temp_r = 0, temp_d = 0, area = 0, z = 0;

	circle->x = 0;
	circle->y = 0;
	circle->r = -1;

	if (num == 1) {
		circle->r = 0;
		circle->x = point[0].x;
		circle->y = point[0].y;
	}
	else if (num == 2) {
		circle->r = sqrt((point[0].x - point[1].x) * (point[0].x - point[1].x) + (point[0].y - point[1].y) * (point[0].y - point[1].y)) / 2;
		circle->x = (point[0].x + point[1].x) / 2;
		circle->y = (point[0].y + point[1].y) / 2;
	}
	else {
		for (int i = 0; i < num - 1; i++) {
			for (int j = i + 1; j < num; j++) {
				temp_r = sqrt((point[i].x - point[j].x) * (point[i].x - point[j].x) + (point[i].y - point[j].y) * (point[i].y - point[j].y)) / 2;
				temp_x = (point[i].x + point[j].x) / 2;
				temp_y = (point[i].y + point[j].y) / 2;
				check = 0;

				for (int k = 0; k < num; k++) {
					temp_d = sqrt((temp_x - point[k].x) * (temp_x - point[k].x) + (temp_y - point[k].y) * (temp_y - point[k].y));
					if (temp_d > temp_r) {
						check = 1;
						break;
					}
				}

				if ((check == 0) && ((circle->r == -1) || (temp_r < circle->r))) {
					circle->r = temp_r;
					circle->x = temp_x;
					circle->y = temp_y;
				}
			}
		}
		for (int i = 0; i < num - 2; i++) {
			for (int j = i + 1; j < num - 1; j++) {
				for (int k = j + 1; k < num; k++) {
					area = ((point[j].x - point[i].x) * (point[k].y - point[i].y) - (point[j].y - point[i].y) * (point[k].x - point[i].x)) / 2;
					(area < 0) ? area *= -1 : area;

					if (area != 0) {
						if (point[i].x == point[j].x) {
							temp_y = (point[i].y + point[j].y) / 2;
							temp_x = (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[k].y) / 2 + (point[j].y + point[k].y) / 2 - (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[i].y) / 2;
						}
						else if (point[j].x == point[k].x) {
							temp_y = (point[j].y + point[k].y) / 2;
							temp_x = (point[k].y - point[i].y) / (point[k].x - point[i].x) * (point[i].y + point[k].y) / 2 + (point[i].y + point[k].y) / 2 - (point[k].y - point[i].y) / (point[k].x - point[i].x) * (point[j].y + point[k].y) / 2;
						}
						else if (point[i].x == point[k].x) {
							temp_y = (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[k].y) / 2 + (point[j].y + point[k].y) / 2 - (point[k].y - point[j].y) / (point[k].x - point[j].x) * (point[j].y + point[i].y) / 2;
							temp_x = (point[i].y + point[j].y) / 2;
						}
						else {			
							temp_y = ((point[j].x * point[j].x + point[j].y * point[j].y - point[i].x * point[i].x - point[i].y * point[i].y) * (point[k].x - point[i].x) - (point[k].x * point[k].x + point[k].y * point[k].y - point[i].x * point[i].x - point[i].y * point[i].y) * (point[j].x - point[i].x)) / (2 * ((point[i].y - point[k].y) * (point[j].x - point[i].x) - (point[i].y - point[j].y) * (point[k].x - point[i].x)));
							temp_x = (point[j].x * point[j].x + point[j].y * point[j].y - point[i].x * point[i].x - point[i].y * point[i].y + (2 * point[i].y - 2 * point[j].y) * temp_y) / (2 * point[j].x - 2 * point[i].x);
						}

						temp_r = sqrt((point[i].x - temp_x) * (point[i].x - temp_x) + (point[i].y - temp_y) * (point[i].y - temp_y));
						check = 0;
					}
					else break;

					for (int d = 0; d < num; d++) {
						temp_d = sqrt((temp_x - point[d].x) * (temp_x - point[d].x) + (temp_y - point[d].y) * (temp_y - point[d].y));

						if (temp_d > temp_r) {
							check = 1;
							break;
						}
					}
					if ((check == 0) && ((circle->r == -1) || (temp_r < circle->r))) {
						circle->r = temp_r;
						circle->x = temp_x;
						circle->y = temp_y;
					}
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int num = 0, err = 0;
	Point *point = NULL;
	Circle *circle = NULL;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &point, &num);
	if (err != 0) return -1;

	circle = (Circle*)calloc(1, sizeof(Circle));

	find_min_circle(point, circle, num);

	fprintf(f_out, "%lf %lf %lf", circle->x, circle->y, circle->r);

	free(point);
	free(circle);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
