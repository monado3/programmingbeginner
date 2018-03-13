#include <stdio.h>

void increment(int*);

int main(){
    int a =10;
    increment(&a);
    printf("%d\n",a);//出力は11
    
    return 0;
}

void increment(int *n){
    (*n)++;
}
