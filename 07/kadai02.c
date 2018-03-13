#include <stdio.h>
#include <stdlib.h>

typedef struct temp{
    char name[20];
    int age;
    double weight;
    double height;
    struct temp *next;
} person;

int main(int argc, char *argv[]){

    FILE *fp;
    int line=0;
    int c;
           
    if (argc != 2) {
        printf("コマンドのあとに一つファイルを指定してください\n");
    }

    if ( ( fp=fopen(argv[1],"r") ) == NULL){
        printf("ファイルの読み込みに失敗しました。\n");
        return 1;
    }

    while((c = getc(fp)) != EOF) {
        if(c == '\n') {
            line++;
        }
    }
    fseek(fp,0,SEEK_SET);

    //格納
    person *list;
    list = (person*)malloc(sizeof(person));

    person *head=list;
    fscanf(fp,"%[^,],%d,%lf,%lf\n",list->name,&(list->age),&(list->weight),&(list->height));
    for (int i=1; i<line; i++) {
        list->next = (person*)malloc(sizeof(person));
        fscanf(fp,"%[^,],%d,%lf,%lf\n",list->next->name,&(list->next->age),&(list->next->weight),&(list->next->height));
        if (i<line-1){
            list = list->next;
        }else{
            list->next->next = NULL;
        }

    }

    //表示
    for (person *offset=head; offset!=NULL; offset = offset->next){
        printf("(name,age,weight,height) = (%s,%d,%f,%f)\n",offset->name,offset->age,offset->weight,offset->height);
    }
    
    return 0;
}
