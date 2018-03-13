#include <stdio.h>
#include <math.h>

int main(){
    int a,b,c,i,con;
    for (a=1;a<1000;a++){
        for (b=a;b<1000;b++){
            for (c=b;c<1000;c++){
                if (a*a + b*b == c*c){
                    con = 0;
                    for (i=2;i<=(a/2)+1;i++){
                        if (a%i==0 && b%i==0 && c%i==0){
                            con = 1;break;
                        }
                    }
                    if (con==0){
                        printf("%d^2 + %d^2 =%d^2\n",a,b,c);
                    }
                }
            }
        }
    }
return 0;
}
