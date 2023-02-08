#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int bintodec(int *phitemp, int stvar)
{
	int temp = 0, base = 1;
	for (int i = stvar - 1; i >= 0; i--)
	{
		if (phitemp[i] == 1)
			temp += base;
		base *= 2;
	}
	return temp;
}

int in(FILE *fin, int *stvar, int ***phi, int **psi)
{
	int err = 0;
	char *str = NULL;
	if (fscanf(fin, "%d", stvar) == 1)
	{
		fscanf(fin, "%*s");
		str = (char*)calloc((1 << (*stvar + 1)) + 1, sizeof(char));
		*phi = (int**)calloc(*stvar, sizeof(int*));
		if ((*phi != NULL) && (str != NULL))
		{
			for (int i = 0; i < *stvar; i++)
			{
				(*phi)[i] = (int*)calloc((1 << (*stvar + 1)), sizeof(int));
				if ((*phi)[i] != NULL)
				{
					fscanf(fin, "%*d %*d %s", str);
					for (int j = 0; j < (1 << (*stvar + 1)); j++)
					{
						if (str[j] == '1')
							(*phi)[i][j] = 1;
						else
							(*phi)[i][j] = 0;
					}
				}
				else
				{
					err = -3;
					break;
				}
			}
			*psi = (int*)calloc((1 << (*stvar + 1)), sizeof(int));
			if (*psi != NULL)
			{
				fscanf(fin, "%*d %*d %s", str);
				for (int i = 0; i < (1 << (*stvar + 1)); i++)
				{
					if (str[i] == '1')
						(*psi)[i] = 1;
					else
						(*psi)[i] = 0;
				}
			}
			else
				err = -4;
			free(str);
		}
		else
			err = -2;
	}
	else
		err = -1;
	return err;
}

void tables(int stvar, int **phi, int *psi, int ***phitable, int ***psitable)
{
	int pos = 0;
	int *phitemp = NULL, *temp = NULL;
	*phitable = (int**)calloc((1 << stvar), sizeof(int*));
	for (int i = 0; i < (1 << stvar); i++)
		(*phitable)[i] = (int*)calloc(2, sizeof(int));
	*psitable = (int**)calloc((1 << stvar), sizeof(int*));
	for (int i = 0; i < (1 << stvar); i++)
		(*psitable)[i] = (int*)calloc(2, sizeof(int));
	phitemp = (int*)calloc(stvar, sizeof(int));
	temp = (int*)calloc((1 << (stvar + 1)), sizeof(int));
	for (int i = 0; i < (1 << (stvar + 1)); i++)
	{
		for (int j = 0; j < stvar; j++)
			phitemp[j] = phi[j][i];
		temp[i] = bintodec(phitemp, stvar);
	}
	for (int i = 0; i < (1 << stvar); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			(*phitable)[i][j] = temp[pos];
			(*psitable)[i][j] = psi[pos];
			pos++;
		}
	}
	free(phitemp);
	free(temp);
}

int equalstates(int stvar, int **phi, int *psi, int ***eqst)
{
	int err = 0, curst1 = 0, curst2 = 0, nextst1 = 0, nextst2 = 0, outsymb1 = 0, outsymb2 = 0;
	int **phitable = NULL, **psitable = NULL;
	bool flag = true;
	*eqst = (int**)calloc((1 << stvar), sizeof(int*));
	if (*eqst != NULL)
	{
		for (int i = 0; i < (1 << stvar); i++)
		{
			(*eqst)[i] = (int*)calloc((1 << stvar), sizeof(int));
			if ((*eqst)[i] == NULL)
			{
				err = -2;
				break;
			}
		}
		tables(stvar, phi, psi, &phitable, &psitable);
		for (int i = 0; i < (1 << stvar); i++)
		{
			for (int j = 0; j < (1 << stvar); j++)
			{
				if (i == j)
					(*eqst)[i][j] = 0;
				else
					(*eqst)[i][j] = 1;
			}
		}
		for (int i = 0; i < (1 << stvar) - 1; i++)
		{
			for (int j = i + 1; j < (1 << stvar); j++)
			{
				flag = true;
				for (int k = 0; k < (1 << (1 << stvar)); k++)
				{
					curst1 = i;
					curst2 = j;
					for (int s = (1 << stvar) - 1; s >= 0; s--)
					{
						if (k & (1 << s))
						{
							nextst1 = phitable[curst1][1];
							outsymb1 = psitable[curst1][1];
							nextst2 = phitable[curst2][1];
							outsymb2 = psitable[curst2][1];
						}
						else
						{
							nextst1 = phitable[curst1][0];
							outsymb1 = psitable[curst1][0];
							nextst2 = phitable[curst2][0];
							outsymb2 = psitable[curst2][0];
						}
						if (outsymb1 != outsymb2)
						{
							(*eqst)[i][j] = 0;
							(*eqst)[j][i] = 0;
							flag = false;
							break;
						}
						curst1 = nextst1;
						curst2 = nextst2;
					}
					if (flag == false)
						break;
				}
			}
		}
		for (int i = 0; i < (1 << stvar); i++)
			free(phitable[i]);
		free(phitable);
		for (int i = 0; i < (1 << stvar); i++)
			free(psitable[i]);
		free(psitable);
	}
	else
		err = -1;
	return err;
}

void out(FILE *fout, int stvar, int **eqst)
{
	for (int i = 0; i < (1 << stvar); i++)
	{
		for (int j = 0; j < (1 << stvar); j++)
		{
			if ((i < j) && (eqst[i][j] == 1))
			{
				for (int k = stvar - 1; k >= 0; k--)
				{
					if (i & (1 << k))
						fprintf(fout, "1");
					else
						fprintf(fout, "0");
				}
				fprintf(fout, " ");
				for (int k = stvar - 1; k >= 0; k--)
				{
					if (j & (1 << k))
						fprintf(fout, "1");
					else
						fprintf(fout, "0");
				}
				fprintf(fout, " ");
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int err = 0, stvar = 0;
		int **phi = NULL, *psi = NULL, **eqst = NULL;
		FILE *fin, *fout;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			err = in(fin, &stvar, &phi, &psi);
			if (err == 0)
			{
				err = equalstates(stvar, phi, psi, &eqst);
				if (err == 0)
				{
					out(fout, stvar, eqst);
					for (int i = 0; i < stvar; i++)
						free(phi[i]);
					free(phi);
					free(psi);
					for (int i = 0; i < (1 << stvar); i++)
						free(eqst[i]);
					free(eqst);
				}
			}
		}
	}
	return 0;
}