#include <stdio.h>
#include <math.h>

long mod_apm(long,long,long);

int main(){
    printf("%ld\n",mod_apm(541,1234,1299709));
    
    return 0;
}

long mod_apm(long a, long p , long m){
    if (p==1) {
        return a;
    }else{
        return (a*mod_apm(a,p-1,m)) % m; 
    }
}
