#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int input(FILE *f_in, int *n, int *num, char **conj) {
	char *str = NULL;

	if (fscanf(f_in, "%d %d", n, num) != 2) return -1;
	
	*conj = (char*)calloc((*n) * (*num), sizeof(char));
	if (*conj == NULL) return -1;
	
	str = (char*)calloc(*n + 1, sizeof(char));
	if (str == NULL) return -1;
	
	for (int i = 0; i < *num; i++) {
		if (fscanf(f_in, "%s", str) == 0) return -1;
		for (int j = 0; j < *n; j++) *(*conj + i * (*n) + j) = str[j];
	}
	
	free(str);
		
	return 0;
}

void blake_2(int n, int num, char *conj) {
	int str_num = num - 1;

	while (str_num != 0) {
		for (int i = 0; i < num; i++) {
			if (i != str_num) {
				for (int j = 0; j < n; j++) {
					if ((*(conj + str_num * n + j) != '*') && (*(conj + str_num * n + j) != '3')) {
						if (*(conj + str_num * n + j) != *(conj + i * n + j)) break;
						if (j == n - 1) {
							for (int k = 0; k < n; k++) *(conj + i * n + k) = '3';
						}
					}
				}
			}
		}
		str_num--;
	}
}

int sort(int n, int num, char *conj) {
	char *temp_conj = NULL;
	temp_conj = (char*)calloc(n, sizeof(char));
	if (temp_conj == NULL) return -1;

	for (int i = num - 2; i >= 0; i--) {
		for (int k = num - 1; k >= i + 1; k--) {
			if (*(conj + i * n + 1) != '3') {
				for (int j = n - 1; j >= 0; j--) {
					if (((*(conj + i * n + j) == '1') && (*(conj + k * n + j) == '0')) || 
						((*(conj + i * n + j) == '*') && (*(conj + k * n + j) == '0')) || 
						((*(conj + i * n + j) == '*') && (*(conj + k * n + j) == '1'))) {
						for (int s = 0; s < n; s++) {
							temp_conj[s] = *(conj + i * n + s);
							*(conj + i * n + s) = *(conj + k * n + s);
							*(conj + k * n + s) = temp_conj[s];
						}
					}
				}
			}
		}
	}
	
	free(temp_conj);

	return 0;
}

void output(FILE *f_out, int n, int num, char *conj) {
	int count = 0, temp_num = num;

	for (int i = 0; i < num; i++) {
		if (*(conj + i * n + 1) == '3') temp_num--;
	}

	fprintf(f_out, "%d %d\n", n, temp_num);

	for (int i = 0; i < num; i++) {
		if (*(conj + i * n + 1) != '3') {
			for (int j = 0; j < n; j++) fprintf(f_out, "%c", *(conj + i * n + j));
			if (i < num - 1) fprintf(f_out, "\n");
		}
		else count++;
		if (count == num) fprintf(f_out, "%d 0", n);
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int err = 0, n = 0, num = 0;
	char *conj = NULL;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &n, &num, &conj);
	if (err != 0) return -1;

	blake_2(n, num, conj);

	err = sort(n, num, conj);
	if (err != 0) return -1;

	output(f_out, n, num, conj);

	free(conj);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
