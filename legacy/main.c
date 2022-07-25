#include <stdio.h>
#include "func.h"
#include <math.h>
#include "integral.h"
#include "root.h"
#include "string.h"

//F1=e^x+2
//F2=-2x+8
//F3= -5/x
double EPSILON1 = 0.001;


double TESTF_const(double x) {
    return 1;
}

double TESTF_linear(double x) {
    return x;
}

double TESTF_parabola(double x) {
    return x * x;
}


void help() {
    fputs("By default -help parameter is passed\n", stdout);
    fputs("All available parameters list\n", stdout);
    fputs("-help Get help\n", stdout);
    fputs("-test Run test root and integral functions\n", stdout);
    fputs("-axis Print x coordinate of intersection points\n", stdout);
    fputs("-iter Print results of each iterations while computing integral\n", stdout);
    fputs("-test Launch default test set-up\n", stdout);
    fputs("-steaps Print results of each iterations while computing root\n", stdout);
    fputs("-area Calculate area shaped by F1,F2,F3\n", stdout);
}

void test() {
    _Bool flag_testsfailed = 0;

    fputs("Testing root function", stdout);
    fputs("on f(x) = x, g(x)= x^2 on segment (0.5,2)\n", stdout);
    double answer = root(TESTF_linear, TESTF_parabola, 0.5, 2, EPSILON1 / 100);
    double difference = answer - 1;
    fprintf(stdout, "Answer:%f\nCorrect answer: 1\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;


    fputs("Testing root function", stdout);
    fputs("on f(x) = e^x +2 , g(x)= x^2 on segment (-1,0.5)\n", stdout);
    answer = root(F1, TESTF_parabola, -5, -1, EPSILON1 / 100);
    difference = answer - (-1.4916442);
    fprintf(stdout, "Answer:%f\nCorrect answer: -1.4916442\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;


    fputs("Testing root function", stdout);
    fputs("on f(x) = x, g(x)= 1 on segment (0.5,2)\n", stdout);
    answer = root(TESTF_linear, TESTF_const, 0.5, 2, EPSILON1 / 100);
    difference = answer - 1;
    fprintf(stdout, "Answer:%f\nCorrect answer: 1\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing root function", stdout);
    fputs("on f(x) = F1(x) =exp(x) + 2, g(x)= F2(x) = -2 * x + 8 on segment (-3,4)\n", stdout);
    answer = root(F1, F2, -3, 4, EPSILON1 / 100);
    difference = answer - 1.2517579314;
    fprintf(stdout, "Answer:%f\nCorrect answer: 1.2517579314\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing root function", stdout);
    fputs("on f(x) = F3(x)= -5 / x, g(x)= F2(x) =  -2 * x + 8 on segment (4,5)\n", stdout);
    answer = root(F3, F2, 4, 5, EPSILON1 / 100);
    difference = answer - 4.54950975;
    fprintf(stdout, "Answer:%f\nCorrect answer: 4.54950975\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing root function", stdout);
    fputs("on f(x) =  F2(x) =  -2 * x + 8, g(x)= F3(x)= -5 / x on segment (-1,-0.3)\n", stdout);
    answer = root(F2, F3, -1, -0.3, EPSILON1 / 100);
    difference = answer - (-0.5495097);
    fprintf(stdout, "Answer:%f\nCorrect answer: -0.5495097\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;


    fputs("Testing root function", stdout);
    fputs("on f(x) = F1(x)= exp(x) + 2, g(x)= F3(x)= -5 / x on segment (-3,-1)\n", stdout);
    answer = root(F1, F3, -3, -1, EPSILON1 / 100);
    difference = answer - (-2.3905367039);
    fprintf(stdout, "Answer:%f\nCorrect answer: -2.3905367039\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;


    if (flag_testsfailed) fprintf(stdout, "\nroot Tests not passed\n\n");
    else fprintf(stdout, "\nroot Tests passed\n\n");
    flag_testsfailed = 0;

    fputs("Testing integral function", stdout);
    fputs("on f(x) = x,(0,5)\n", stdout);
    answer = integral(TESTF_linear, 0, 5, EPSILON1 / 100);
    difference = answer - 12.5;
    fprintf(stdout, "Answer:%f\nCorrect answer: 12.5\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing integral function", stdout);
    fputs("on f(x) = 1,(0,25)\n", stdout);
    answer = integral(TESTF_const, 0, 25, EPSILON1 / 10);
    difference = answer - 25;
    fprintf(stdout, "Answer:%f\nCorrect answer: 25\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing integral function ", stdout);
    fputs("on f(x) = F1(x)= exp(x) + 2,(-10,3)\n", stdout);
    answer = integral(F1, -10, 3, EPSILON1 / 10);
    difference = answer - 46.085491523;
    fprintf(stdout, "Answer:%f\nCorrect answer: 46.085491523\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing integral function ", stdout);
    fputs("on f(x) = x^2,(-5,1)\n", stdout);
    answer = integral(TESTF_parabola, -5, 1, EPSILON1 / 10);
    difference = answer - 42;
    fprintf(stdout, "Answer:%f\nCorrect answer: 42\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing integral function ", stdout);
    fputs("on f(x) = sin(x),(-4,4)\n", stdout);
    answer = integral(sin, -4, 4, EPSILON1 / 10);
    difference = answer - 0;
    fprintf(stdout, "Answer:%f\nCorrect answer: 0\ndifference: %f\n", answer, difference);


    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    if (flag_testsfailed) fprintf(stdout, "\nintegral Tests not passed\n");
    else fprintf(stdout, "\nintegral Tests passed\n");
}


double area()//calculate area shaped by F1,F2,F3
{
    double points[3];
    points[0] = root(F1, F3, -3, -1, EPSILON1 / 100);
    points[1] = root(F2, F3, -1, -0.3, EPSILON1 / 100);
    points[2] = root(F1, F2, -3, 4, EPSILON1 / 100);
    double Area = 0;
    Area += integral(F3, points[0], points[1], EPSILON1 / 100);
    Area += integral(F2, points[1], points[2], EPSILON1 / 100);
    Area -= integral(F1, points[0], points[2], EPSILON1 / 100);
    printf("Area shaped by F1,F2,F3: %f\n", Area);
}

int main(int argc, char **argv) {
    OPTION_ITER = 0;
    OPTION_AXIS = 0;
    OPTION_STEPS = 0;
    _Bool testoption = 0;
    _Bool helpoption = 0;
    _Bool areaoption = 0;
    if (argc == 1) help();
    else {
        for (int i = 1; i < argc; i++) {
            char *str = argv[i];
            if (!strcmp(str, "-iter")) OPTION_ITER = 1;
            else {
                if (!strcmp(str, "-axis")) OPTION_AXIS = 1;
                else {
                    if (!strcmp(str, "-steps")) OPTION_STEPS = 1;
                    else {
                        if (!strcmp(str, "-help")) helpoption = 1;
                        else {
                            if (!strcmp(str, "-test"))
                                testoption = 1;
                            else {
                                if (!strcmp(str, "-area"))
                                    areaoption = 1;
                                else {
                                    helpoption = 1;
                                    testoption = 0;
                                    areaoption = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (testoption) test();
    if (helpoption) help();
    if (areaoption) area();
    return 0;
}
