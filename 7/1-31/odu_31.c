#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funks_31.h"

double nystrom_c[4];
double nystrom_a[4][4];
double nystrom_a_[4][4];
double nystrom_b[4];
double nystrom_b_[4];

int iter_num = 1;

// Коэффициенты Нюстрема 4 порядка
void nystrom_init() {
    nystrom_c[0] = 0.0;
    nystrom_c[1] = 1.0 / 2.0;
    nystrom_c[2] = 1.0 / 2.0;
    nystrom_c[3] = 1.0;

    nystrom_a[1][0] = 1.0 / 2.0;
    nystrom_a[2][0] = 0.0;
    nystrom_a[2][1] = 1.0 / 2.0;
    nystrom_a[3][0] = 0.0;
    nystrom_a[3][1] = 0.0;
    nystrom_a[3][2] = 1.0;

    nystrom_a_[1][0] = 1.0 / 8.0;
    nystrom_a_[2][0] = 1.0 / 8.0;
    nystrom_a_[2][1] = 0.0;
    nystrom_a_[3][0] = 0.0;
    nystrom_a_[3][1] = 0.0;
    nystrom_a_[3][2] = 1.0 / 2.0;

    nystrom_b[0] = 1.0 / 6.0;
    nystrom_b[1] = 2.0 / 6.0;
    nystrom_b[2] = 2.0 / 6.0;
    nystrom_b[3] = 1.0 / 6.0;

    nystrom_b_[0] = 1.0 / 6.0;
    nystrom_b_[1] = 1.0 / 6.0;
    nystrom_b_[2] = 1.0 / 6.0;
    nystrom_b_[3] = 0.0;
}

// Скалярное произведение
double dot(double *arr1, double *arr2, int size) {
    double res = 0;
    for (int i = 0; i < size; i++) res += arr1[i] * arr2[i];
    return res;
}

// Квадратичная ошибка
double get_error(double *arr1, double *arr2, int n) {
    double res = 0.0;
    for (int i = 0; i < n; i += 2) res += (arr1[i / 2] - arr2[i]) * (arr1[i / 2] - arr2[i]);
    res = sqrt(res) / n;
    return res;
}

// y'' = f(x, y, y')
double y_eq(double x, double y1, double y2) {
    return -p(x, y1) * y2 - q(x, y1) * y1 + f(x, y1);
}

// Метод Нюстрема
// y(x0) = y0
// y'(x0) = z0
double nystrom(double x0, double x1, double y0, double z0, int n, double *ys) {
    double x = x0;
    double y = y0;
    double z = z0;
    double h = (x1 - x0) / n;

    ys[0] = y0;

    for (int i = 0; i < n; i++) {
        double k[4] = {0.0};

        for (int j = 0; j < 4; j++) {
            double temp1 = x + nystrom_c[j] * h;
            double temp2 = y + nystrom_c[j] * h * z + h * h * dot(k, nystrom_a_[j], j);
            double temp3 = z + h * dot(k, nystrom_a[j], j);
            k[j] = y_eq(temp1, temp2, temp3);
        }

        x += h;
        y += h * (z + h * dot(k, nystrom_b_, 4));
        z += h * dot(nystrom_b, k, 4);
        ys[i + 1] = y;
    }

    return ys[n];
}

// Подбор параметра n
int find_n(double x0, double x1, double y0, double z0, int n, double eps) {
    double *ys_n = (double*)calloc((n + 1), sizeof(double));
    nystrom(x0, x1, y0, z0, n, ys_n);

    double error = eps + 1;

    while (error > eps) {
        n *= 2;
        double *ys_2n = (double*)calloc((n + 1), sizeof(double));
        nystrom(x0, x1, y0, z0, n, ys_2n);
        error = get_error(ys_n, ys_2n, n + 1);

        free(ys_n);
        ys_n = ys_2n;
    }

    free(ys_n);

    return n;
}

// f(z0)
// Вычисляет Нюстрема для конкретного z0 и best_n
double F(double x0, double x1, double y0, double z0, int n, double eps) {
    int best_n = find_n(x0, x1, y0, z0, n, eps);
    double *ys_temp = (double*)calloc((best_n + 1), sizeof(double));
    double y1_temp = nystrom(x0, x1, y0, z0, best_n, ys_temp);
    free(ys_temp);
    return y1_temp;
}

// Метод Ньютона
// y(x0) = y0
// y(x1) = y1
// z(x0) = ?
// Вычисляет z0
double newton(double x0, double x1, double y0, double y1, int n, double eps) {
    nystrom_init();

    double z0 = 0;
    double delta = 1e-15;

    double y1_temp = F(x0, x1, y0, z0, n, eps);

    while (fabs(y1_temp - y1) > eps) {
        double df = (F(x0, x1, y0, z0 + delta, n, eps) - F(x0, x1, y0, z0 - delta, n, eps)) / (2 * delta);
        z0 = (y1 - y1_temp) / df + z0;
        y1_temp = F(x0, x1, y0, z0, n, eps);
        iter_num++;
    }
    
    return z0;
}

int get_iter_num() {
    return iter_num;
}
