/*
=============================================================================================
PROJECT: Gradient descent of given function z=f(x,y)
FILE: Gradient.c
DESCRIPTION:
This is a simple script for finding local minimum of a 2 argument function z=f(x,y) starting from given point (x,y).
MinimumCalculator uses constant size step vectors while MinimumCalculator2 uses anti-gradient vector itself.
The second one works better (in my example) since it breaks from loop after smaller number of iterations and the closer 
it gets to minimum, the more precise is estimation. With constant step size an oscillation around minimum is likely to occur.
NOTE: Calculated point is a stationary point that is candidate for local minimum. If you want to check if it is actually minimum, you have to
calculate Hessian matrix determinant and examine cases. So the point calculated may not be an actual local minimum. Function also may be flat.
DATE:   24.3.2024
AUTHOR: Pavle Totic
=============================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//prototypes
double f(double x, double y);
double df_dx(double x, double y, double h);
double df_dy(double x, double y, double h);
void antigrad(double pdx, double pdy, double* antigradient);
double Intensity(double* vector);
void Step(double* antigradient, double* stepvector);
void MinimumCalculator(double x, double y, double* antigradient, double* stepvector, double* minimum, double h);
void MinimumCalculator2(double x, double y, double* antigradient, double* minimum, double h);

//2 argument function f(x,y)
double f(double x, double y) {
    return sin(5*x) * cos(5*y) / 5;
}
//Example functions:
// x*x+y*y
//sin(5*x) * cos(5*y) / 5
//pow(x, 2) + pow(y, 2) + 2
//x*y (works for x=1, y=1)

//partial derivative x
double df_dx(double x, double y, double h) {
    return (f(x + h, y) - f(x, y)) / h;
}
//partial derivative y
double df_dy(double x, double y, double h) {
    return (f(x, y + h) - f(x, y)) / h;
}
//antigradiant
void antigrad(double pdx, double pdy, double* antigradient) {
    antigradient[0] = -pdx;
    antigradient[1] = -pdy;
}
//intensity of vector
double Intensity(double* vector) {
    return sqrt(pow(vector[0], 2) + pow(vector[1], 2));
}
//constant size stepvector (normalizes antigradient)
void Step(double* antigradient, double* stepvector) {
    stepvector[0] = antigradient[0] / Intensity(antigradient);
    stepvector[1] = antigradient[1] / Intensity(antigradient);
}
//this function uses constant size stepvector to look for local minimum
//make sure to adjust parameters so it can reach minimum with given number of iterations i
void MinimumCalculator(double x, double y, double* antigradient, double* stepvector, double* minimum, double h) {
    float k = 0.001;//size adjustment for stepvector
    int i = 1; //i is the maximum number of iterations
    double min_x = x;
    double min_y = y;
    double min_f = f(x, y);
    int minimum_found = 1;
    while (Intensity(antigradient) > 0.001 && i < 10000) {
        Step(antigradient, stepvector);
        printf("    step vector:[%.6lf %.6lf]\n", stepvector[0], stepvector[1]);
        x = x + stepvector[0] * k;
        y = y + stepvector[1] * k;
        double pdx = df_dx(x, y, h);
        double pdy = df_dy(x, y, h);
        antigrad(pdx, pdy, antigradient);
        
        double current_f = f(x, y);
        //clip with -30
        if (current_f < min_f && min_f > -30) {
            min_x = x;
            min_y = y;
            min_f = current_f;
        }
        else {
            printf("\nCouldn't find local minimum from given point, try another point\n");
            minimum_found = 0;
            break;
        }
        //adjust step size
        if (i == 9000) {
            k = 0.0001;
        }
        min_x = x;
        min_y = y;
        printf("current point:[%.3lf %.3lf %.3lf]\n", min_x, min_y ,min_f);
        i++;
        printf("\n");
    }
    if (minimum_found == 1) {
        minimum[0] = min_x;
        minimum[1] = min_y;
        printf("The closest local minimum of given function is: [%.3lf %.3lf %.3lf]\n", minimum[0], minimum[1], f(minimum[0], minimum[1]));
    }
}
//this function uses antigradient itself to find minimum
void MinimumCalculator2(double x, double y, double* antigradient, double* minimum, double h) {
    float k = 0.1;
    int i = 1; //i is the maximum number of iterations
    double min_x = x;
    double min_y = y;
    double min_f = f(x, y);
    int minimum_found = 1;
    while (Intensity(antigradient) > 0.00001 && i < 10000) {
        printf("anti-gradiant:[%.6lf %.6lf]\n", antigradient[0], antigradient[1]);
        x = x + antigradient[0] * k;
        y = y + antigradient[1] * k;
        double pdx = df_dx(x, y, h);
        double pdy = df_dy(x, y, h);
        antigrad(pdx, pdy, antigradient);
        double current_f = f(x, y);
        //clipping with -1000
        if (current_f < min_f && min_f > -1000) {
            min_x = x;
            min_y = y;
            min_f = current_f;
        }
        else {
            printf("\nCouldn't find local minimum from given point, try another point\n");
            minimum_found = 0;
            break;
        }
        min_x = x;
        min_y = y;
        printf("current point:[%.3lf %.3lf %.3lf]\n", min_x, min_y, min_f);
        i++;
        printf("\n");
    }
    if (minimum_found == 1) {
        minimum[0] = min_x;
        minimum[1] = min_y;
        printf("The closest local minimum of given function is: [%.3lf %.3lf %.3lf]\n", minimum[0], minimum[1], f(minimum[0], minimum[1]));
    }
}

int main() {

    double antigradient[2];
    double stepvector[2];
    double minimum[2];

    double h = 0.0001;//step for derivative
    double x = 2;//starting point x
    double y = 1;//starting point y

    double pdx = df_dx(x, y, h); //partial derivative on x, v=(1,0,0)
    double pdy = df_dy(x, y, h); //partial derivative on y, v=(0,1,0)
    antigrad(pdx, pdy, antigradient);
    //MinimumCalculator(x, y, antigradient, stepvector, minimum, h);
    MinimumCalculator2(x, y, antigradient, minimum, h);
    return 0;
}
