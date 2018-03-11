#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 100

void cal(double*,double*,double*,double*,double*,int);

int main(int argc,char *argv[]){
    FILE *fp;
    int line=0;
    char c;

    if(argc!=2) {
        printf("コマンドの後に１つファイルを指定してください。\n");
        return 1;
    }

    if ((fp= fopen(argv[1], "r"))==NULL) {
        printf("ファイルを開くのに失敗しました\n");
        return 1;
    }

    while((c = getc(fp)) != EOF) {
        if(c == '\n') {
            line++;
        }
    }

    fseek(fp,0,SEEK_SET);

    double *a,*h,*w,*max,*min,*mean,*stdev;

    max=(double*)malloc(sizeof(double));
    min=(double*)malloc(sizeof(double));
    mean=(double*)malloc(sizeof(double));
    stdev=(double*)malloc(sizeof(double));
    a=(double*)malloc(sizeof(double)*line);
    h=(double*)malloc(sizeof(double)*line);
    w=(double*)malloc(sizeof(double)*line);

    for (int i=0; i<line; i++) {
        fscanf(fp,"%*[^,],%lf,%lf,%lf\n",a+i,h+i,w+i);
    }

    cal(a,max,min,mean,stdev,line);
    printf("Age : (max,min,mean,stdev) = (%lf, %lf, %lf, %lf)\n",
           *max,*min,*mean,*stdev);

    cal(h,max,min,mean,stdev,line);
    printf("Height : (max,min,mean,stdev) = (%lf, %lf, %lf, %lf)\n",
           *max,*min,*mean,*stdev);

    cal(w,max,min,mean,stdev,line);
    printf("Weight : (max,min,mean,stdev) = (%lf, %lf, %lf, %lf)\n",
           *max,*min,*mean,*stdev);

    free(max);
    free(min);
    free(mean);
    free(stdev);
    free(a);
    free(h);
    free(w);

    fclose(fp);

    return 0;
}

void cal(double *x,double *max,double *min,double *mean,double *stdev,int line){
    *max=0,*min=1000,*mean=0,*stdev=0;

    for (int i=0; i<line; i++) {
        if ( *(x+i) > *max) {
            *max = *(x+i);
        }
        if ( *(x+i) < *min) {
            *min = *(x+i);
        }
        *mean= *mean + *(x+i);
    }
    *mean = *mean/line;
    for (int i=0; i<line; i++) {
        *stdev= *stdev + pow(*(x+i)-*mean,2);
    }
    *stdev= sqrt( *stdev/(double)line );
}
