#include <stdio.h>
int is_prime(int);/*引数が素数場合1，それ以外場合0を返す*/
int main() {
    int i;
    for(i =2; i <=1000; i++) {
        if(is_prime(i)==1) {
            printf("%d is prime\n", i);
        }
    }
}
int is_prime(int n) {
    int ans=1;
    int j;
    for (j=2;j<n;j++){
        if (n%j == 0){
            ans=0;
            break;
        }
    }
return ans;
}

