#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable: 4996)

int bintodec(bool *temp, int len)
{
	int tempint = 0, base = 1;
	for (int i = len - 1; i >= 0; i--)
	{
		if (temp[i] == true)
			tempint += base;
		base *= 2;
	}
	return tempint;
}

void dectobin(int i, int *ibin)
{
	int k = 0;
	while (i != 0)
	{
		if (i % 2 == 0)
			ibin[k] = 0;
		else
			ibin[k] = 1;
		i >>= 1;
		k++;
	}
}

bool* in(FILE *fin, int *err)
{
	int k = 0, n = 0;
	bool *f = NULL;
	char *str = NULL;
	*err = 0;
	if (fscanf(fin, "%d %d ", &k, &n) == 2)
	{
		f = (bool*)calloc(8, sizeof(bool));
		str = (char*)calloc(9, sizeof(char));
		if ((f != NULL) && (str != NULL))
		{
			if (fscanf(fin, "%s", str) != 0)
			{
				for (int i = 0; i < 8; i++)
				{
					if (str[i] == '1')
						f[i] = true;
					else
						f[i] = false;
				}
			}
			else
				*err = -3;
			free(str);
			str = NULL;
		}
		else
			*err = -2;
	}
	else
		*err = -1;
	return f;
}

bool findfs(bool *f, bool *fs, bool *g1, bool *g2)
{
	int tempint = 0, pos = 0, num = 2, *tempfuncbin = NULL;
	bool stopflag = true, *temp = NULL, *tempf = NULL, *func = NULL, *tempfunc = NULL;
	temp = (bool*)calloc(3, sizeof(bool));
	tempf = (bool*)calloc(4,sizeof(bool));
	tempfunc = (bool*)calloc(4, sizeof(bool));
	tempfuncbin = (int*)calloc(4, sizeof(int));
	for (int i = 0; i < 16; i++)
	{
		if (fs[i])
			num++;
	}
	func = (bool*)calloc(num * 4, sizeof(bool));
	for (int i = 0; i < 4; i++)
	{
		*(func + 0 * 4 + i) = g1[i];
		*(func + 1 * 4 + i) = g2[i];
	}
	int j = 2;
	for (int i = 0; i < 16; i++)
	{
		if (fs[i])
		{
			dectobin(i, tempfuncbin);
			int m = 0;
			for (int n = 3; n >= 0; n--)
			{
				if (tempfuncbin[n] == 1)
					tempfunc[m] = true;
				else
					tempfunc[m] = false;
				m++;
			}
			for (int k = 0; k < 4; k++)
				*(func + j * 4 + k) = tempfunc[k];
			j++;
		}
	}
	for (int j1 = 0; j1 < num; j1++)
	{
		for (int j2 = 0; j2 < num; j2++)
		{
			for (int j3 = 0; j3 < num; j3++)
			{
				for (int i = 0; i < 4; i++)
				{
					temp[0] = *(func + j1 * 4 + i);
					temp[1] = *(func + j2 * 4 + i);
					temp[2] = *(func + j3 * 4 + i);
					tempint = bintodec(temp, 3);
					tempf[i] = f[tempint];
				}
				pos = bintodec(tempf, 4);
				if (fs[pos] == false)
				{
					fs[pos] = true;
					stopflag = false;
				}
			}
		}
	}
	free(tempfuncbin);
	tempfuncbin = NULL;
	free(tempfunc);
	tempfunc = NULL;
	free(temp);
	temp = NULL;
	free(tempf);
	tempf = NULL;
	free(func);
	func = NULL;
	return stopflag;
}

bool* span(bool *f)
{
	bool *fs = NULL, stopflag = false;
	fs = (bool*)calloc(16, sizeof(bool));
	bool g1[4] = {false, true, false, true};
	bool g2[4] = {false, false, true, true};
	while (!fs[14] && !fs[8] && !stopflag)
	{
		stopflag = findfs(f, fs, g1, g2);
	}
	fs[3] = true;
	fs[5] = true;
	if (fs[14] || fs[8])
	{
		for (int i = 0; i < 16; i++)
			fs[i] = true;
	}
	return fs;
}

void out(FILE *fout, bool *fs)
{
	int *ibin = NULL;
	ibin = (int*)calloc(4, sizeof(int));
	if (ibin != NULL)
	{
		for (int i = 0; i < 16; i++)
		{
			if (fs[i])
			{
				fprintf(fout, "2 2 ");
				dectobin(i, ibin);
				for (int j = 3; j >= 0; j--)
					fprintf(fout, "%d", ibin[j]);
				fprintf(fout, "\n");
			}
		}
		free(ibin);
		ibin = NULL;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		FILE *fin, *fout;
		int err = 0;
		bool *f = NULL, *fs = NULL;
		fin = fopen(argv[1], "r");
		fout = fopen(argv[2], "w");
		if ((fin != NULL) && (fout != NULL))
		{
			f = in(fin, &err);
			if (err == 0)
			{
				fs = span(f);
				out(fout, fs);
				free(fs);
				fs = NULL;
			}
			free(f);
			f = NULL;
			fclose(fin);
			fclose(fout);
		}
	}
	return 0;
}