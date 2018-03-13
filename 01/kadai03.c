#include <stdio.h>
int main(){
  int a,b,c;
  for (a=1;a<1000;a++){
    for (b=a;b<1000;b++){
      for (c=b;c<1000;c++){
	if (a*a + b*b == c*c){
	  printf("%d^2 + %d^2 =%d^2\n",a,b,c);
	}
      }
    }
  }
  return 0;
}
