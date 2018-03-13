#include <stdio.h>
#include <math.h>
#define EPSILON 0.001

double f(double);
double dfdx(double);
double newton(double);

int main() {
    double x0 =1.0;
    double solution = newton(x0);
    printf("solution is %f\n", solution);
    
    return 0;
}

double f(double x){
    return exp(x) + x;
}

double dfdx(double x){
    return exp(x) + 1;
}

double newton(double x){
    double n1 = x - f(x)/dfdx(x);
    if ( fabs(n1-x) < EPSILON ){
        return n1;
    }else{
        return newton(n1);
    }
}
