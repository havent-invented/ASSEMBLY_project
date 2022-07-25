#include <math.h>
#include <stdio.h>
#include "integral.h"

_Bool OPTION_ITER;


double integral(double (*f)(double), double a, double b, double eps)//calculation of integral using rectangle method
{
    double sum = 0;
    double prev_sum = sum + 32 * eps;
    unsigned n = 40;
    while (fabs(sum - prev_sum) / 3 > eps) {
        prev_sum = sum;
        sum = 0;
        double shift = fabs(b - a) / n;
        for (double i = a; i < b; i += shift)
            sum += f(i) * shift;
        if (OPTION_ITER)
            printf("Integral sum with n= : %u is %f\n", n, sum);//printing integral sum on each calculated iteration
        n *= 2;
    }
    return sum;
}
