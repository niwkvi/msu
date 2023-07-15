#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lss_17_04.h"

#pragma warning (disable: 4996)

int n = 0;
double *A = NULL, *B = NULL, *X = NULL, *tmp = NULL;

int flag_errors = 0, flag_matrix = 0, flag_time = 0;

char *in_filename = "lss_17_04_in.txt";
char *out_filename = "lss_17_04_out.txt";

void errors(int error_id) {
    if (flag_errors) {
        if (error_id == -2) {
            fprintf(stderr, "Memory Allocation Error");
        } else if (error_id == -3) {
            fprintf(stderr, "Command Line Error");
        } else if (error_id == -4) {
            fprintf(stderr, "Input Data Error");
        } else if (error_id == -5) {
            fprintf(stderr, "Output Data Error");
        } else if (error_id == -6) {
            fprintf(stderr, "-h or -?");
        }
    }
}

void mem_free() {
    if (A != NULL) free(A);
    if (B != NULL) free(B);
    if (X != NULL) free(X);
    if (tmp != NULL) free(tmp);
}

void mem_alloc() {
    A = (double *) calloc(n * n, sizeof(double));
    B = (double *) calloc(n, sizeof(double));
    X = (double *) calloc(n, sizeof(double));
    tmp = (double *) malloc(lss_memsize_17_04(n));

    if (A == NULL || B == NULL || X == NULL || tmp == NULL) {
        mem_free();
        errors(-2);
        exit(-2);
    }
}

void print_matrix() {
    printf("Matrix A\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lf\t", A[n * i + j]);
        }
        printf("\n");
    }

    printf("Matrix B\n");
    for (int i = 0; i < n; i++) {
        printf("%lf\t", B[i]);
    }
}

void print_execution_time(clock_t time_start, clock_t time_end) {
    double time = 1.0 * (time_end - time_start) / CLOCKS_PER_SEC;
    printf("Time: %lf s\n\n", time);
}

void print_help() {
    printf("Usage: lss [input_file_name] [output_file_name] [options] \n");
    printf("Where options include: \n");
    printf("  -d        print debug messages [default OFF] \n");
    printf("  -e        print errors [default OFF] \n");
    printf("  -p        print matrix [default OFF] \n");
    printf("  -t        print execution time [default OFF] \n");
    printf("  -h, -?    print this and exit \n");
    printf("Default input_file_name value is lss_17_04_in.txt, default output_file_name value is lss_17_04_out.txt.\n");
}

int len(const char *str) {
    int count;
    for (count = 0; str[count] != '\0'; count++);
    return count;
}

void parse_command_line(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {

        if (argv[i][0] == '-' && len(argv[i]) == 2) {
            if (argv[i][1] == 'd') {
                flag_debug = 1;
            } else if (argv[i][1] == 'e') {
                flag_errors = 1;
            } else if (argv[i][1] == 'p') {
                flag_matrix = 1;
            } else if (argv[i][1] == 't') {
                flag_time = 1;
            } else if (argv[i][1] == 'h' || argv[i][1] == '?') {
                print_help();
                errors(-6);
                exit(-6);
            } else {
                errors(-3);
                exit(-3);
            }
        } else {
            if (i == 1) {
                in_filename = argv[1];
            } else if (i == 2) {
                out_filename = argv[2];
            } else {
                errors(-3);
                exit(-3);
            }
        }
    }
}

void input() {
    int temp;

    FILE *in_file = fopen(in_filename, "r");
    if (in_file == NULL) {
        errors(-4);
        exit(-4);
    }

    temp = fscanf(in_file, "%d", &n);
    if (temp != 1 || n <= 0) {
        errors(-4);
        exit(-4);
    }

    mem_alloc();

    for (int i = 0; i < (n * n); i++) {
        temp = fscanf(in_file, "%lf", &A[i]);
        if (temp != 1) {
            errors(-4);
            exit(-4);
        }
    }

    for (int i = 0; i < n; i++) {
        temp = fscanf(in_file, "%lf", &B[i]);
        if (temp != 1) {
            errors(-4);
            exit(-4);
        }
    }

    fclose(in_file);
}

void output(int ans) {
    FILE *out_file = fopen(out_filename, "w");
    if (out_file == NULL) {
        errors(-5);
        exit(-5);
    }

    if (ans == 1) {
        fprintf(out_file, "%d", 0);
        return;
    }

    fprintf(out_file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        fprintf(out_file, "%1.9lf\n", X[i]);
    }
}

int main(int argc, char *argv[]) {
    int ans;

    parse_command_line(argc, argv);
    input();

    if (flag_matrix) {
        print_matrix();
    }

    clock_t time_start = clock();
    ans = lss_17_04(n, A, B, X, tmp);
    clock_t time_end = clock();

    if (flag_time) {
        print_execution_time(time_start, time_end);
    }

    output(ans);
    mem_free();

    return ans;
}
