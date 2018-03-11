#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc,char *argv[]){
    FILE *fp1,*fp2;
    char *ans;
    int pp,p,c,n;
    ans=(char*)malloc(sizeof(char)*100000);

    if(argc!=3) {
        printf("コマンドの後に2つファイルを指定してください。\n");
        return 1;
       }
    if ((fp1= fopen(argv[1], "r"))==NULL) {
        printf("ファイルを開くのに失敗しました\n");
        return 1;
    }
    if ((fp2= fopen(argv[2], "w"))==NULL) {
        printf("ファイルを開くのに失敗しました\n");
        return 1;
       }

    pp='.';
    p=' ';
    c=getc(fp1);
    int i=0;
    while ( (n=getc(fp1)) != EOF) {
        if (p==' ' && c=='i' && ( n==' ' || n=='\'') ) {
            ans[i]=toupper(c);
        }else if (pp== '.' || pp=='?' || pp=='!') {
            if (p=='\"') {
                ans[i]=c;
                i++;
                ans[i]=toupper(n);
                pp=p;
                p=c;
                c=n;
                n=getc(fp1);
            }else if ( c =='\"') {
                ans[i]=c;
                i++;
                ans[i]=toupper(n);
                pp=p;
                p=c;
                c=n;
                n=getc(fp1);
            }else{
                ans[i]=toupper(c);
            }
        }else{
            ans[i]=c;
        }
        pp=p;
        p=c;
        c=n;
        i++;
    }

    fputs(ans,fp2);

    free(ans);
    fclose(fp1);
    fclose(fp2);

    return 0;
}
