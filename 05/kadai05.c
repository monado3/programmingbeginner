#include <stdio.h>
#include <string.h>

int roman2num(char*);

int main(){
    // Examples
    printf("XIV = %d\n", roman2num("XIV"));//14
    printf("CDXCV = %d\n", roman2num("CDXCV"));//495
    printf("MCMXLV = %d\n", roman2num("MCMXLV"));//1945
    printf("MMMCMXCIX = %d\n", roman2num("MMMCMXCIX"));//3999
    
    return 0;
}

int roman2num(char *s){
    int list[]= {1,5,10,50,100,500,1000};
    int ans=0;
    int len = strlen(s);
    char t[len+1];
    int i;
    for (i=0;i<len;i++){
        switch (*(s+i)){
            case 'M': *(t+i)='g';break;
            case 'D': *(t+i)='f';break;
            case 'C': *(t+i)='e';break;
            case 'L': *(t+i)='d';break;
            case 'X': *(t+i)='c';break;
            case 'V': *(t+i)='b';break;
            case 'I': *(t+i)='a';break;
        }
    }
    for (i=0;i<len-1;i++){
        if (*(t+i) < *(t+i+1)){
            ans = ans - list[*(t+i)-'a'];
        }else{
            ans = ans + list[*(t+i)-'a'];
        }
    }
    ans = ans + list[*(t+i)-'a'];
    
    return ans;
}
