#include <math.h>
#include <stdio.h>
#include "root.h"

double DELTA1 = 0.00001;

_Bool OPTION_AXIS = 0;
_Bool OPTION_STEPS = 0;
double rightderiv(double x, double (*F)(double))//rightside first deriv
{
    return (F(x + DELTA1) - F(x)) / DELTA1;
}


double deriv(double x, double (*F)(double))//1-st derivetive
{
    return (F(x + DELTA1) - F(x - DELTA1)) / (2 * DELTA1);
}


double derivsecond(double x, double (*F)(double))//2-nd deriv
{
    //(F(x+2eps)-2F(x)+F(x-2eps))/(2eps)**2
    return (F(x + 2 * DELTA1) + F(x - 2 * DELTA1) - 2 * F(x)) / 4 / DELTA1 / DELTA1;
}


double root(double (*f)(double), double (*g)(double), double a, double b, double eps) {//root calculation
    int signofderiv = (derivsecond((a + b) / 2, f) - derivsecond((a + b) / 2, g)) ? 1 : -1;
    signofderiv *= (deriv((a + b) / 2, f) - deriv((a + b) / 2, g)) ? 1 : -1;//signum of F'(x)*F''(x)
    double c = a * (f(b) - g(b)) - b * (f(a) - g(a));//Chord method calculations
    unsigned steps=0;//steps counter
    while ((f(c + eps) - g(c + eps)) * (f(c - eps) - g(c - eps)) > 0) {
        c = a * (f(b) - g(b)) - b * (f(a) - g(a));
        c /= (f(b) - g(b)) - f(a) + g(a);
        if (signofderiv > 0)
            a = c;
        else
            b = c;
        steps++;
        if (OPTION_STEPS)
            printf("Chord method. Root with n = %u steps is %f\n", steps, c);//printing root with n steps on each calculated iteration
    }
    if (OPTION_AXIS)
        printf("Interaction point: %f , %f\n", c, f(c));//displaying point of where f(x)=g(x) depending on (OPTION_AXIS) value
    return c;
}

double rootD(double (*f)(double), double (*g)(double), double a, double b, double eps,double (*d1)(double),double (*d2)(double)) {//root calculation
    int signofderiv = (derivsecond((a + b) / 2, f) - derivsecond((a + b) / 2, g)) ? 1 : -1;
    signofderiv *= (d1((a + b) / 2) - d2((a + b) / 2)) ? 1 : -1;//signum of F'(x)*F''(x)
    double d; 
    double c;
    if(signofderiv>0)
        c=b;
    else c=a;
    c = c - (f(c)-g(c))/(d1(c)-d2(c));//Tangent method calculations
    unsigned steps=0;//steps counter
    double checkval=(f(c + eps) - g(c + eps)) * (f(c - eps) - g(c - eps)) ;
   
    while ( (f(c + eps) - g(c + eps)) * (f(c - eps) - g(c - eps))   > 0) {
        c = c - (f(c)-g(c))/(d1(c)-d2(c));

        steps++;
        if (OPTION_STEPS)
            printf("Tangent method.Root with n = %u steps is %f\n", steps, c);//printing root with n steps on each calculated iteration
    }
    
    if (OPTION_AXIS)
        printf("Interaction point: %f , %f\n", c, f(c));//displaying point of where f(x)=g(x) depending on (OPTION_AXIS) value
    return c;
}



