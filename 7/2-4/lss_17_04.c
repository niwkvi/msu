#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "lss_17_04.h"

const double EPS = 1e-8;
int flag_debug;

size_t lss_memsize_17_04(int n) {
    return n * sizeof(double);
}

int lss_17_04(int n, double *A, double *B, double *X, double *tmp) {
    if (flag_debug) {
        printf("\nAlgorithm has started\n\n");
    }

    clock_t time_start = clock();

    for (int i = 0; i < n; i++) {

        if (flag_debug) {
            clock_t time_now = clock();
            double time = 1.0 * (time_now - time_start) / CLOCKS_PER_SEC;
            printf("Searching for the max element in row #%d\n", i);
            printf("Time: %lf s\n\n", time);
        }

        double main_elem_abs = fabs(A[n * i]);

        int main_col = 0;
        for (int j = 1; j < n; j++) {
            if (main_elem_abs <= fabs(A[n * i + j])) {
                main_elem_abs = fabs(A[n * i + j]);
                main_col = j;
            }
        }

        if (main_elem_abs < EPS) {
            if (fabs(B[i]) >= EPS) {
                return 1;
            }
            tmp[i] = -1;
			continue;
		}

        if (flag_debug) {
            clock_t time_now = clock();
            double time = 1.0 * (time_now - time_start) / CLOCKS_PER_SEC;
            printf("Dividing by the max element in row #%d\n", i);
            printf("Time: %lf s\n\n", time);
        }

        double main_elem = A[n * i + main_col];
        for (int j = 0; j < n; j++) {
            A[n * i + j] /= main_elem;
        }
        B[i] /= main_elem;

        if (flag_debug) {
            clock_t time_now = clock();
            double time = 1.0 * (time_now - time_start) / CLOCKS_PER_SEC;
            printf("Eliminating the elements under and above the max element in row #%d\n", i);
            printf("Time: %lf s\n\n", time);
        }

        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            double cur_elem = A[n * j + main_col];
            for (int k = 0; k < n; k++) {
                A[n * j + k] -= A[n * i + k] * cur_elem;
            }
            B[j] -= B[i] * cur_elem;
        }

        tmp[i] = main_col;
    }

    if (flag_debug) {
        clock_t time_now = clock();
        double time = 1.0 * (time_now - time_start) / CLOCKS_PER_SEC;
        printf("Saving the answer in the given X array\n");
        printf("Time: %lf s\n\n", time);
    }

    for (int i = 0; i < n; i++) {
        if (fabs(tmp[i] - (-1)) >= EPS) {
            X[(int)tmp[i]] = B[i];
        }
    }

    if (flag_debug) {
        clock_t time_now = clock();
        double time = 1.0 * (time_now - time_start) / CLOCKS_PER_SEC;
        printf("Algorithm has finished\n");
        printf("Time: %lf s\n\n", time);
    }

    return 0;
}
