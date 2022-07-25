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
    fputs("-test Launch default tests set-up\n", stdout);
    fputs("-steaps Print results of each iterations while computing root\n", stdout);
    fputs("-area Calculate area shaped by F1,F2,F3 form specified file\n", stdout);
}


   void test(_Bool OPTION_TANGENT) {
    _Bool flag_testsfailed = 0;

    fputs("Testing root function", stdout);
    fputs("on f(x) = x, g(x)= x^2 on segment (0.5,2)\n", stdout);
    double answer = root(TESTF_linear, TESTF_parabola, 0.5, 2, EPSILON1 / 100);
    double difference = answer - 1;
    fprintf(stdout, "Answer:%f\nCorrect answer: 1\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;


    fputs("Testing root function", stdout);
    fputs("on f(x) = x, g(x)= 1 on segment (0.5,2)\n", stdout);
    answer = root(TESTF_linear, F1, 0.5, 2, EPSILON1 / 100);
    difference = answer - 1;
    fprintf(stdout, "Answer:%f\nCorrect answer: 1\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;


    fputs("Testing root function", stdout);
    fputs("on f(x) = F3(x)= -5 / x, g(x)= F2(x) =  -2 * x + 8 on segment (4,5)\n", stdout);
    if (OPTION_TANGENT)
        answer = rootD(F2, F3, 4, 5, EPSILON1 / 100, Der2, Der3);
    else
        answer = root(F2, F3, 4, 5, EPSILON1 / 100);

    difference = answer - 4.54950975;
    fprintf(stdout, "Answer:%f\nCorrect answer: 4.54950975\ndifference: %f\n", answer, difference);
    if (difference > EPSILON1 || (-difference) > EPSILON1) flag_testsfailed = 1;

    fputs("Testing root function", stdout);
    fputs("on f(x) =  F2(x) =  -2 * x + 8, g(x)= F3(x)= -5 / x on segment (-1,-0.3)\n", stdout);
    if (OPTION_TANGENT)
        answer = rootD(F2, F3, -1, -0.3, EPSILON1 / 100, Der2, Der3);
    else
        answer = root(F2, F3, -1, -0.3, EPSILON1 / 100);
    difference = answer - (-0.5495097);
    fprintf(stdout, "Answer:%f\nCorrect answer: -0.5495097\ndifference: %f\n", answer, difference);
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


double area_var8()//calculate area shaped by F1,F2,F3 with variant 8functions
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

double area(double interval1, double interval2, _Bool OPTION_TANGENT)//calculate area shaped by F1,F2,F3
{
    double points[3];
    
    
    printf("Interval: [%lf,%lf]\n", interval1, interval2);
    if (OPTION_TANGENT) {
        points[0] = rootD(F1, F2, interval1, interval2, EPSILON1 / 100, Der1, Der3);
        points[1] = rootD(F2, F3, interval1, interval2, EPSILON1 / 100, Der2, Der3);
        points[2] = rootD(F3, F1, interval1, interval2, EPSILON1 / 100, Der1, Der2);

    } else {
        points[0] = root(F1, F2, interval1, interval2, EPSILON1 / 100);
        points[1] = root(F2, F3, interval1, interval2, EPSILON1 / 100);
        points[2] = root(F3, F1, interval1, interval2, EPSILON1 / 100);
    }

    double tmpmas[3];
    tmpmas[0]=points[0];
    tmpmas[1]=points[1];
    tmpmas[2]=points[2];

    unsigned indexmas[3];
    indexmas[0]=0;
    indexmas[1]=1;
    indexmas[2]=2;
    
    




    if (tmpmas[1] < tmpmas[0]) {
        double tmp = tmpmas[1];
        tmpmas[1] = tmpmas[0];
        tmpmas[0] = tmp;

         tmp = indexmas[1];
        indexmas[1] = indexmas[0];
        indexmas[0] = tmp;
    }
    if (tmpmas[2] < tmpmas[0]) {
        double tmp = tmpmas[2];
        tmpmas[2] = tmpmas[0];
        tmpmas[0] = tmp;

         tmp = indexmas[2];
        indexmas[2] = indexmas[0];
        indexmas[0] = tmp;
    }
    if (tmpmas[2] < tmpmas[1]) {
        double tmp = tmpmas[2];
        tmpmas[2] = tmpmas[1];
        tmpmas[1] = tmp;
        tmp = indexmas[2];
        indexmas[2] = indexmas[1];
        indexmas[1] = tmp;
    }


    double (*u[3]) (double a);

    printf("Interval: [%lf,%lf]\n", tmpmas[0], tmpmas[2]);
    
    int positivesign=0;

    u[indexmas[0]]=F1;
    u[indexmas[1]]=F2;
    u[indexmas[2]]=F3;


    if (indexmas[1] == 0)//F1 F2
    {
        positivesign = F3(points[indexmas[1]]) - F2(points[indexmas[1]]) > 0 ? 1 : -1;
    }

    if (indexmas[1] == 1)//F2 F3
        positivesign = F1(points[indexmas[1]]) - F2(points[indexmas[1]]) > 0 ? 1 : -1;


    if (indexmas[1] == 2)//F1 F3
        positivesign = F2(points[indexmas[1]]) - F3(points[indexmas[1]]) > 0 ? 1 : -1;

    // checking middle integrals for >


    double Area = 0;
    Area += integral(u[0], points[indexmas[0]], points[indexmas[1]], EPSILON1 / 100);
    Area += integral(u[2], points[indexmas[1]], points[indexmas[2]], EPSILON1 / 100);
    Area -= integral(u[1], points[indexmas[0]], points[indexmas[2]], EPSILON1 / 100);
    printf("Area shaped by F1,F2,F3: %f\n", positivesign * Area);
}

int main(int argc, char **argv) {
    setbuf(stdout, 0);
    double interval1 = -1, interval2 = 1;//interval limits
    FILE *tmpFile = fopen("filename", "r");//getting filename to pass interval limits into main
    char filename1[50];
    fgets(filename1, 48, tmpFile);
    fclose(tmpFile);

    FILE *limitsFile = fopen(filename1, "r");


    fscanf(limitsFile, "%lf", &interval1);
    fscanf(limitsFile, "%lf", &interval2);
    fclose(limitsFile);
    _Bool OPTION_TANGENT = 0;
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
            if (!strcmp(str, "-D"))
                OPTION_TANGENT = 1;
            else {
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
    }
    if (testoption) test(OPTION_TANGENT);
    if (helpoption) help();
    if (areaoption) area(interval1, interval2, OPTION_TANGENT);
    return 0;
}

