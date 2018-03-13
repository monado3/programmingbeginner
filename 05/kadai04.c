#include <stdio.h>
#include <string.h>

void uppercase(char*);

int main(){
    char s[]="hello world";
    uppercase(s);
    printf("%s\n",s);
    
    return 0;
}

void uppercase(char *s){
    int len=strlen(s);
    char temp[len+1];
    strcpy(temp,s);
    for (int i=0;i<len;i++){
        if ('a'<=*(s+i) && *(s+i)<='z'){
            *(s+i)=*(temp+i)-32;
        }    
    }
}
