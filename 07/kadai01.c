#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int c;
    int n;
} monomial;

monomial* construct_monomial(int c,int n) {
    monomial* temp;
    temp=(monomial*)malloc(sizeof(monomial));
    temp->c = c;
    temp->n = n;
    
    return temp;
}
    
void diff_monomial(monomial *m) {
    int tempc = m->c;
    int tempn = m->n;
    m->c = (tempn)*(tempc);
    m->n = tempn-1;
}

void print_monomial(monomial *m) { 
     printf("%d*x^%d\n", m->c, m->n);
}

int main() {
    monomial *m1;
    m1 = construct_monomial(-4,10);
    print_monomial(m1);// 表示は-4*x^10  
    diff_monomial(m1);   
    print_monomial(m1);

    return 0;
}