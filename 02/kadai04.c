#include <stdio.h>
#include <math.h>
int is_prime(int);/*引数が素数場合1，それ以外場合0を返す*/

int main(){
    int i;
    double sum= 1.0, pai;
    for(i =2; i <=10000; i++) {
        if(is_prime(i)==1) {
            sum*= 1.0 - pow(i,-2);
        }
    }
    pai = sqrt(6.0 / sum);
    printf("π = %f\n",pai);
return 0;
}

int is_prime(int n) {
    int ans=1;
    int j;
    for (j=2;j<=(n/2);j++){
        if (n%j == 0){
            ans=0;
            break;
        }
    }
return ans;
}
