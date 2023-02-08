#include <math.h>

double p(double x, double y) {
    return -(x + 4) / (2 * x);
}

double q(double x, double y) {
    return (1 + 4 / x) / (2 * x);
}

double f(double x, double y) {
    return x * x / 2;
}

double real(double x) {
    double C1 = (358 - 195 * M_E) / (12 * (1 - M_E));
    double C2 = 163 / (12 * (M_E - 1) * M_E * M_E);
    return x * (C1 + C2 * exp(x / 2)) - x * (x * x / 2 + 2 * x);
}
