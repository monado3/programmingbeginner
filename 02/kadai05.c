#include <stdio.h>
int gcd(int,int);

int main(){
    int r;
    int a =8733;
    int b =64681;
    r = gcd(a,b);
    printf("gcd(%d, %d) = %d\n", a, b, r);
return 0;
}

int gcd(int a,int b){
    int t;
    while (b !=0){
        t = b;
        b = a % b;
        a = t;
    }
return a;
}
