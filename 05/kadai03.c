#include <stdio.h>
#include <string.h>

void reverse(char*);

int main(){
    char s[]="hello";
    reverse(s);
    printf("%s\n",s);// 出力䛿"olleh"return
    
    return 0;
}

void reverse(char *s){
    int len = strlen(s);
    char temp[len+1];
    strcpy(temp,s);
    for (int i=0;i<len;i++){
        *(s+i) = *(temp+len-i-1);
    }
}
