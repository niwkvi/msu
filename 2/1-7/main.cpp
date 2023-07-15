#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int bin_to_dec(bool *num_bin, int len) {
	int num_dec = 0, base = 1;
	for (int i = len - 1; i >= 0; i--) {
		if (num_bin[i] == true) num_dec += base;
		base *= 2;
	}
	return num_dec;
}

void dec_to_bin(int num_dec, bool *num_bin) {
	int pos = 0;
	while (num_dec != 0) {
		if (num_dec % 2 == 0) num_bin[pos] = false;
		else num_bin[pos] = true;

		num_dec >>= 1;
		pos++;
	}
}

int input(FILE *f_in, bool **func) {
	int k = 0, n = 0;
	char *str = NULL;

	if (fscanf(f_in, "%d %d", &k, &n) != 2) return -1;

	*func = (bool*)calloc(8, sizeof(bool));
	if (*func == NULL) return -1;

	str = (char*)calloc(9, sizeof(char));
	if (str == NULL) return -1;

	if (fscanf(f_in, "%s", str) == 0) return -1;

	for (int i = 0; i < 8; i++) {
		if (str[i] == '1') (*func)[i] = true;
		else (*func)[i] = false;
	}

	free(str);

	return 0;
}

int find_funcs(bool *func, bool *funcs, bool *g1, bool *g2, bool *stop_flag) {
	int num = 2, temp_int = 0;
	bool *temp = NULL, *temp_func_1 = NULL, *temp_func_1_bin = NULL, *temp_func_2 = NULL, *funcs_found = NULL;

	*stop_flag = true;
	
	temp = (bool*)calloc(3, sizeof(bool));
	if (temp == NULL) return -1;

	temp_func_1 = (bool*)calloc(4, sizeof(bool));
	if (temp_func_1 == NULL) return -1;

	temp_func_2 = (bool*)calloc(4,sizeof(bool));
	if (temp_func_2 == NULL) return -1;

	temp_func_1_bin = (bool*)calloc(4, sizeof(bool));
	if (temp_func_1_bin == NULL) return -1;

	for (int i = 0; i < 16; i++) {
		if (funcs[i]) num++;
	}

	funcs_found = (bool*)calloc(num * 4, sizeof(bool));
	if (funcs_found == NULL) return -1;

	for (int i = 0; i < 4; i++) {
		*(funcs_found + 0 * 4 + i) = g1[i];
		*(funcs_found + 1 * 4 + i) = g2[i];
	}

	int pos_funcs = 2;

	for (int i = 0; i < 16; i++) {
		if (funcs[i]) {
			int pos_func = 0;

			dec_to_bin(i, temp_func_1_bin);

			for (int j = 3; j >= 0; j--) {
				temp_func_1[pos_func] = temp_func_1_bin[j];
				pos_func++;
			}

			for (int j = 0; j < 4; j++) *(funcs_found + pos_funcs * 4 + j) = temp_func_1[j];
			pos_funcs++;
		}
	}

	for (int j0 = 0; j0 < num; j0++) {
		for (int j1 = 0; j1 < num; j1++) {
			for (int j2 = 0; j2 < num; j2++) {
				for (int i = 0; i < 4; i++) {
					temp[0] = *(funcs_found + j0 * 4 + i);
					temp[1] = *(funcs_found + j1 * 4 + i);
					temp[2] = *(funcs_found + j2 * 4 + i);

					temp_int = bin_to_dec(temp, 3);
					temp_func_2[i] = func[temp_int];
				}

				int pos = bin_to_dec(temp_func_2, 4);

				if (funcs[pos] == false) {
					funcs[pos] = true;
					*stop_flag = false;
				}
			}
		}
	}

	free(temp);
	free(temp_func_1);
	free(temp_func_1_bin);
	free(temp_func_2);
	free(funcs_found);

	return 0;
}

int span(bool *func, bool **funcs) {
	int err = 0;
	bool stop_flag = false;

	*funcs = (bool*)calloc(16, sizeof(bool));
	if (*funcs == NULL) return -1;

	bool g1[4] = {false, true, false, true};
	bool g2[4] = {false, false, true, true};

	while (!(*funcs)[14] && !(*funcs)[8] && !stop_flag) {
		err = find_funcs(func, *funcs, g1, g2, &stop_flag);
		if (err != 0) return -1;
	}

	(*funcs)[3] = true;
	(*funcs)[5] = true;

	if ((*funcs)[14] || (*funcs)[8]) {
		for (int i = 0; i < 16; i++) (*funcs)[i] = true;
	}

	return 0;
}

int output(FILE *f_out, bool *funcs) {
	bool *num_bin = NULL;

	num_bin = (bool*)calloc(4, sizeof(bool));
	if (num_bin == NULL) return -1;

	for (int i = 0; i < 16; i++) {
		if (funcs[i]) {
			fprintf(f_out, "2 2 ");

			dec_to_bin(i, num_bin);

			for (int j = 3; j >= 0; j--)
				fprintf(f_out, "%d", num_bin[j]);
			fprintf(f_out, "\n");
		}
	}

	free(num_bin);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int err = 0;
	bool *func = NULL, *funcs = NULL;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &func);
	if (err != 0) return -1;

	err = span(func, &funcs);
	if (err != 0) return -1;

	err = output(f_out, funcs);
	if (err != 0) return -1;

	free(func);
	free(funcs);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
