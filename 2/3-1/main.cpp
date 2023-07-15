#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int bin_to_dec(int *num_bin, int len) {
	int temp = 0, base = 1;
	for (int i = len - 1; i >= 0; i--) {
		if (num_bin[i] == 1) temp += base;
		base *= 2;
	}
	return temp;
}

int input(FILE *f_in, int *n, int ***phi, int **psi) {
	char *str = NULL;

	if (fscanf(f_in, "%d", n) != 1) return -1;

	int num_states_plus = (1 << (*n + 1));

	fscanf(f_in, "%*s");

	str = (char*)calloc(num_states_plus + 1, sizeof(char));
	if (str == NULL) return -1;
	
	*phi = (int**)calloc(*n, sizeof(int*));
	if (*phi == NULL) return -1;

	for (int i = 0; i < *n; i++) {
		(*phi)[i] = (int*)calloc(num_states_plus, sizeof(int));
		if ((*phi)[i] == NULL) return -1;
		
		fscanf(f_in, "%*d %*d %s", str);
		
		for (int j = 0; j < num_states_plus; j++) {
			if (str[j] == '1') (*phi)[i][j] = 1;
			else (*phi)[i][j] = 0;
		}
	}

	*psi = (int*)calloc(num_states_plus, sizeof(int));
	if (*psi == NULL) return -1;
	
	fscanf(f_in, "%*d %*d %s", str);
	
	for (int i = 0; i < num_states_plus; i++) {
		if (str[i] == '1') (*psi)[i] = 1;
		else (*psi)[i] = 0;
	}

	free(str);

	return 0;
}

int tables(int n, int **phi, int *psi, int ***phi_table, int ***psi_table) {
	int *phi_temp = NULL, *phi_temp_dec = NULL;

	int num_states = (1 << n);
	int num_states_plus = (1 << (n + 1));

	*phi_table = (int**)calloc(num_states, sizeof(int*));
	if (*phi_table == NULL) return -1;

	for (int i = 0; i < num_states; i++) {
		(*phi_table)[i] = (int*)calloc(2, sizeof(int));
		if ((*phi_table)[i] == NULL) return -1;
	}

	*psi_table = (int**)calloc(num_states, sizeof(int*));
	if (*psi_table == NULL) return -1;

	for (int i = 0; i < num_states; i++) {
		(*psi_table)[i] = (int*)calloc(2, sizeof(int));
		if ((*psi_table)[i] == NULL) return -1;
	}

	phi_temp = (int*)calloc(n, sizeof(int));
	if (phi_temp == NULL) return -1;

	phi_temp_dec = (int*)calloc(num_states_plus, sizeof(int));
	if (phi_temp_dec == NULL) return -1;

	for (int i = 0; i < num_states_plus; i++) {
		for (int j = 0; j < n; j++) phi_temp[j] = phi[j][i];
		phi_temp_dec[i] = bin_to_dec(phi_temp, n);
	}

	int pos = 0;

	for (int i = 0; i < num_states; i++) {
		for (int j = 0; j < 2; j++) {
			(*phi_table)[i][j] = phi_temp_dec[pos];
			(*psi_table)[i][j] = psi[pos];
			pos++;
		}
	}

	free(phi_temp);
	free(phi_temp_dec);

	return 0;
}

int find_equal_states(int n, int **phi, int *psi, int ***equal_states) {
	int err = 0, cur_state_1 = 0, cur_state_2 = 0, next_state_1 = 0, next_state_2 = 0, out_1 = 0, out_2 = 0;
	int **phi_table = NULL, **psi_table = NULL;
	bool flag = true;

	int num_states = (1 << n);
	
	*equal_states = (int**)calloc(num_states, sizeof(int*));
	if (*equal_states == NULL) return -1;

	for (int i = 0; i < num_states; i++) {
		(*equal_states)[i] = (int*)calloc(num_states, sizeof(int));
		if ((*equal_states)[i] == NULL) return -1;
	}

	err = tables(n, phi, psi, &phi_table, &psi_table);
	if (err != 0) return -1;

	for (int i = 0; i < num_states; i++) {
		for (int j = 0; j < num_states; j++) {
			if (i == j) (*equal_states)[i][j] = 0;
			else (*equal_states)[i][j] = 1;
		}
	}

	for (int i = 0; i < num_states - 1; i++) {
		for (int j = i + 1; j < num_states; j++) {
			flag = true;

			for (int k = 0; k < (1 << num_states); k++) {
				cur_state_1 = i;
				cur_state_2 = j;

				for (int s = num_states - 1; s >= 0; s--) {
					if (k & (1 << s)) {
						next_state_1 = phi_table[cur_state_1][1];
						out_1 = psi_table[cur_state_1][1];

						next_state_2 = phi_table[cur_state_2][1];
						out_2 = psi_table[cur_state_2][1];
					}
					else {
						next_state_1 = phi_table[cur_state_1][0];
						out_1 = psi_table[cur_state_1][0];

						next_state_2 = phi_table[cur_state_2][0];
						out_2 = psi_table[cur_state_2][0];
					}

					if (out_1 != out_2) {
						(*equal_states)[i][j] = 0;
						(*equal_states)[j][i] = 0;
						flag = false;
						break;
					}

					cur_state_1 = next_state_1;
					cur_state_2 = next_state_2;
				}

				if (flag == false) break;
			}
		}
	}

	for (int i = 0; i < (1 << n); i++) free(phi_table[i]);
	free(phi_table);

	for (int i = 0; i < (1 << n); i++) free(psi_table[i]);
	free(psi_table);

	return 0;
}

void output(FILE *f_out, int n, int num_states, int **equal_states) {
	for (int i = 0; i < num_states; i++) {
		for (int j = 0; j < num_states; j++) {
			if ((i < j) && (equal_states[i][j] == 1)) {
				for (int k = n - 1; k >= 0; k--) {
					if (i & (1 << k)) fprintf(f_out, "1");
					else fprintf(f_out, "0");
				}
				fprintf(f_out, " ");
				for (int k = n - 1; k >= 0; k--) {
					if (j & (1 << k)) fprintf(f_out, "1");
					else fprintf(f_out, "0");
				}
				fprintf(f_out, " ");
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) return -1;

	FILE *f_in, *f_out;
	int err = 0, n = 0;
	int **phi = NULL, *psi = NULL, **equal_states = NULL;

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");
	if (f_in == NULL || f_out == NULL) return -1;

	err = input(f_in, &n, &phi, &psi);
	if (err != 0) return -1;

	err = find_equal_states(n, phi, psi, &equal_states);
	if (err != 0) return -1;

	int num_states = (1 << n);

	output(f_out, n, num_states, equal_states);

	for (int i = 0; i < n; i++) free(phi[i]);
	free(phi);

	free(psi);

	for (int i = 0; i < num_states; i++) free(equal_states[i]);
	free(equal_states);

	fclose(f_in);
	fclose(f_out);

	return 0;
}
