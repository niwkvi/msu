#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable :4996)

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int *m1 = NULL, *m2 = NULL, *m3 = NULL;
        int n1 = 0, n2 = 0, n3 = 0, tmp = 0;
        int i, j, k;

        FILE *in, *out;
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if (in != NULL)
        {
            if (fscanf(in, "%d", &n1) == 1)
            {
                m1 = (int*)malloc(n1 * sizeof(int));
                for (j = 0; j < n1; j++)
                {
                    if (fscanf(in, "%d", m1[j]) != 1)
                    {
                        break;
                    }
                }

                if (fscanf(in, "%d", &n2) == 1)
                {
                    m2 = (int*)malloc(n2 * sizeof(int));
                    for (j = 0; j < n2; j++)
                    {
                        if (fscanf(in, "%d", m2[j]) != 1)
                        {
                            break;
                        }
                    }


                    n3 = n1 + n2;

                    m3 = (int*)malloc(n3 * sizeof(int));
                    for (k = 0, i = 0; k < n1; k++, i++) m3[k] = m1[i];
                    for (k = n1, j = 0; k < n3; k++, j++) m3[k] = m2[j];
                    for (int i = n3 - 1; i > 0; i--)
                    {
                        for (int j = 0; j < i; j++)
                            if (m3[j] > m3[j + 1])
                            {
                                int tmp = m3[j];
                                m3[j] = m3[j + 1];
                                m3[j + 1] = tmp;
                            }
                    }
                    fprintf(out, "%d ", n3);
                    for (int i = 0; i < n3; ++i) fprintf(out, "%d ", &m3[i]);

                }
            }
        }
    }
    return 0;
}