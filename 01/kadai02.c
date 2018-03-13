#include <stdio.h>
int main(){
  int n = 158340421;
  int i;
  for ( i=1; i<1000; i++ ){
    if (i*i*i==n){
      printf("%dの三乗根は %d\n",n,i);
    }
  }
  return 0;
}
