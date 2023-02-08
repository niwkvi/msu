#ifndef INC_31_DRAW_GRAPH_H
#define INC_31_DRAW_GRAPH_H

unsigned char *DoubleArrayToByteArray(double *data, size_t length);
void WriteToFile(double *data, size_t dataLength, char *filename);
double *ByteArrayToDoubleArray(unsigned char *data, size_t length);
int draw_graph(double *xs, double *my_sol, double *real_sol, int n);

#endif
