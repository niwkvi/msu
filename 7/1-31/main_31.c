#include <stdio.h>
#include <stdlib.h>
#include "odu_31.h"
#include "funks_31.h"
#include "draw_graph.h"

double *xs = NULL;
double *ys = NULL;
double *ys_real = NULL;

// y'' + p(x)y'+ q(x)y = f(x, y)
// y(x0) = y0_main
// y(x1) = y1_main
// [x0, x1]

int errors(int error_code) {
    if (error_code == -1) fprintf(stderr, "Can't open the input file\n");
    else if (error_code == -2) fprintf(stderr, "Not enough input values\n");
    else if (error_code == -3) fprintf(stderr, "n and eps have to be > 0\n");
    else if (error_code == -4) fprintf(stderr, "x1 has to be > x0\n");
    else if (error_code == -5) fprintf(stderr, "Can't open the output file\n");
    else if (error_code == -6) fprintf(stderr, "Can't allocate memory\n");
    return -1;
}

int input(char *in_filename, double *x0, double *x1, double *y0, double *y1, int *n, double *eps) {
    FILE *in_file = fopen(in_filename, "r");
    if (in_file == NULL) return errors(-1);

    int input_count = fscanf(in_file, "%lf %lf %lf %lf %d %lf", x0, x1, y0, y1, n, eps);

    if (input_count != 6) return errors(-2);
    else if (*n <= 0 || *eps <= 0) return errors(-3);
    else if (*x1 <= *x0) return errors(-4);

    fclose(in_file);

    return 0;
}

int output(char *out_filename, int n, int best_n) {
    FILE *out_file = fopen(out_filename, "w");
    if (out_file == NULL) return errors(-5);

    fprintf(out_file, "%d\n", get_iter_num());
    for (int i = 0; i <= best_n; i += best_n / n) fprintf(out_file, "%lf %lf\n", xs[i], ys[i]);

    fclose(out_file);

    return 0;
}

int new_mem(int best_n) {
    xs = (double*)calloc((best_n + 1), sizeof(double));
    ys = (double*)calloc((best_n + 1), sizeof(double));
    ys_real = (double*)calloc((best_n + 1), sizeof(double));

    if (xs == NULL || ys == NULL || ys_real == NULL) return errors(-6);

    return 0;
}

void free_mem() {
    free(xs);
    free(ys);
    free(ys_real);
}

int solve(double x0, double x1, double y0, double y1, int n, double eps, int *best_n) {
    double best_z0 = newton(x0, x1, y0, y1, n, eps);
    *best_n = find_n(x0, x1, y0, best_z0, n, eps);

    int err = new_mem(*best_n);
    if (err != 0) return err;

    nystrom(x0, x1, y0, best_z0, *best_n, ys);

    double h = (x1 - x0) / *best_n;

    for (int i = 0; i <= *best_n; i++) {
        double x = x0 + i * h;
        xs[i] = x;
        ys_real[i] = real(x);
    }

    return 0;
}

int main() {
    char *in_filename = "in.txt";
    char *out_filename = "out.txt";

    double x0, x1, y0, y1, eps;
    int n, best_n;

    printf("\nStarting!\n");

    printf("Input is in process... ");
    int err = input(in_filename, &x0, &x1, &y0, &y1, &n, &eps);
    if (err != 0) return err;
    printf("Success!\n");

    printf("Solve is in process... ");
    err = solve(x0, x1, y0, y1, n, eps, &best_n);
    if (err != 0) return err;
    printf("Success!\n");

    printf("Output is in process... ");
    err = output(out_filename, n, best_n);
    if (err != 0) return err;
    printf("Success!\n");

    printf("Success!\n");

    free_mem();
    
    return 0;
}
