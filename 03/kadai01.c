#include <stdio.h>

double P(double,double);

int main(){
    printf("%f\n",P(16,0.5));
    printf("%f\n",P(32,0.7));
}

double P(double n ,double x){
    if (n==0){
        return 1;
    } else if (n==1){
        return x;
    } else{
        return ((2*n-1)*x*P(n-1,x)-(n-1)*P(n-2,x))/n;
    }
}
