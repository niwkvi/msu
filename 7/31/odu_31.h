#ifndef INC_31_ODU_31_H
#define INC_31_ODU_31_H

void nystrom_init();
double dot(double *arr1, double *arr2, int size);
double get_error(double *arr1, double *arr2, int n);
double y_eq(double x, double y1, double y2);
double nystrom(double x0, double x1, double y0, double z0, int n, double *ys);
int find_n(double x0, double x1, double y0, double z0, int n, double eps);
double F(double x0, double x1, double y0, double z0, int n, double eps);
double newton(double x0, double x1, double y0, double y1, int n, double eps);
int get_iter_num();

#endif
