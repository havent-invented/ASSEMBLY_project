#ifndef ROOT_H
#define ROOT_H

//calculating root of (f(x)-g(x))=0 in range of [a,b]
extern _Bool OPTION_AXIS;
extern _Bool OPTION_STEPS;

double root(double (*f)(double), double (*g)(double), double a, double b, double eps);
double rootD(double (*f)(double), double (*g)(double), double a, double b, double eps,double (*d1)(double),double (*d2)(double)) ;

#endif
