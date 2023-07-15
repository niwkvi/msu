#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int pow(int k, int n) {
	int res = 1;
	for (int i = 0; i < n; i++) res *= k;
	return res;
}

int input(FILE *f_in, int *k, int *n, int *num, int **func) {
	int temp = 0;
	char *str = NULL;

	if (fscanf(f_in, "%d %d", k, n) != 2) return -1;

	*num = pow(*k, *n);

	*func = (int*)calloc(*num, sizeof(int));
	if (*func == NULL) return -1;
	
	str = (char*)calloc(*num + 1, sizeof(char));
	if (str == NULL) return -1;

	if (fscanf(f_in, "%s", str) == 0) return -1;

	for (int i = 0; i < *num; i++) {
		temp = str[i] - '0';
		if (temp > 9) temp = str[i] - 'A' + 10;
		(*func)[i] = temp;
	}

	free(str);

	return 0;
}

int is_monotone(int k, int n, int num, int *func, int *ans) {
	int len = 0, count_1 = 0, count_2 = 0;
	bool flag = false;
	int **sets = NULL;

	len = num / k;

	sets = (int**)calloc(num, sizeof(int*));
	if (sets == NULL) return -1;
	
	for (int i = 0; i < num; i++) {
		sets[i] = (int*)calloc(n, sizeof(int));
		if (sets[i] == NULL) return -1;
	}
	
	for (int i = 0; i < n; i++) {
		count_1 = 0;
		count_2 = 1;

		for (int j = 0; j < num; j++) {
			for (int s = j; s < len * count_2; s++) sets[s][i] = count_1 % k;
			count_1++;
			count_2++;
			j += (len - 1);
		}

		len /= k;
	}

	for (int i = 0; i < num - 1; i++) {
		for (int j = i + 1; j < num; j++) {
			flag = true;

			for (int s = 0; s < n; s++) {
				if (sets[i][s] >= sets[j][s]) flag = false;
			}

			if (flag) {
				if (func[i] > func[j]) {
					for (int i = 0; i < num; i++) free(sets[i]);
					free(sets);

					*ans = 0;
					return 0;
				}
			}
		}
	}

	*ans = 1;

	for (int i = 0; i < num; i++) free(sets[i]);
	free(sets);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int *func = NULL, err = 0, k = 0, n = 0, num = 0, ans = 0;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &k, &n, &num, &func);
	if (err != 0) return -1;
	
	err = is_monotone(k, n, num, func, &ans);
	if (err != 0) return -1;

	fprintf(f_out, "%d", ans);

	free(func);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
