#ifndef INTEGRAL_H
#define INTEGRAL_H

extern _Bool OPTION_ITER;


//calculating integral of F in range of [a,b]
double integral(double (*f)(double), double a, double b, double eps);


#endif

