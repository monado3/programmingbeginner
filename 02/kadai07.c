#include <stdio.h>
#include <math.h>

int is_prime(int);

int main(){
  /* 1000までの偶数についてゴールドバッハ予想を満たすように式を列挙 */
    int i,j,k;
    for (i=4;i<=1000;i=i+2){
        for (j=2;j<=i-2;j++){
            if ( is_prime(j)==1 && is_prime(i-j) ){
                printf("%d = %d + %d\n",i,j,i-j);break;
            }
        }
    }
return 0;    
}

int is_prime(int n){
    /* nが素数なら1を返す。素数でないなら0を返す。*/
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
