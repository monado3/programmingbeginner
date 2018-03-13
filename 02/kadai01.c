#include <stdio.h>
#include <math.h>

int main(){
  int i;
  double sigma=0,pai;
  for (i=1;i<1000000;i++){
    sigma=sigma + 1/(pow(i,2)*pow(2,i-1));
    }
  pai=sqrt(6*sigma+6*pow(log(2),2));
  printf("π=%f\n",pai);
  return 0;
}
